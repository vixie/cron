/* Copyright 1988,1990,1993,1994 by Paul Vixie
 * All rights reserved
 */

/*
 * Copyright (c) 1997,2000 by Internet Software Consortium, Inc.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#if !defined(lint) && !defined(LINT)
static char rcsid[] = "$Id: cron.c,v 1.4 2000/01/02 20:53:38 vixie Exp $";
#endif

#define	MAIN_PROGRAM

#include "cron.h"

static	void	usage(void),
		run_reboot_jobs(cron_db *),
		cron_tick(cron_db *),
		cron_sync(void),
		cron_sleep(void),
		sigchld_handler(int),
		sighup_arm(void),
		sighup_handler(int),
		parse_args(int c, char *v[]);

static void
usage(void) {
	fprintf(stderr, "usage:  %s [-x debugflag[,...]]\n", ProgramName);
	exit(ERROR_EXIT);
}

int
main(int argc, char *argv[]) {
	cron_db	database;

	ProgramName = argv[0];

	setlocale(LC_ALL, "");

#if defined(BSD)
	setlinebuf(stdout);
	setlinebuf(stderr);
#endif

	parse_args(argc, argv);

	(void) signal(SIGCHLD, sigchld_handler);
	(void) signal(SIGHUP, sighup_handler);

	acquire_daemonlock(0);
	set_cron_uid();
	set_cron_cwd();

	putenv("PATH="_PATH_DEFPATH);

	/* if there are no debug flags turned on, fork as a daemon should.
	 */
# if DEBUGGING
	if (DebugFlags) {
# else
	if (0) {
# endif
		(void) fprintf(stderr, "[%ld] cron started\n", (long)getpid());
	} else {
		switch (fork()) {
		case -1:
			log_it("CRON",getpid(),"DEATH","can't fork");
			exit(0);
			break;
		case 0:
			/* child process */
			log_it("CRON",getpid(),"STARTUP","fork ok");
			(void) setsid();
			break;
		default:
			/* parent process should just die */
			_exit(0);
		}
	}

	acquire_daemonlock(0);
	database.head = NULL;
	database.tail = NULL;
	database.mtime = (time_t) 0;
	load_database(&database);
	run_reboot_jobs(&database);
	cron_sync();
	while (TRUE) {
# if DEBUGGING
		if (!(DebugFlags & DTEST))
# endif /*DEBUGGING*/
			cron_sleep();

		load_database(&database);

		/* do this iteration
		 */
		cron_tick(&database);

		/* sleep 1 minute
		 */
		TargetTime += 60;
	}
}

static void
run_reboot_jobs(cron_db *db) {
	user *u;
	entry *e;

	for (u = db->head; u != NULL; u = u->next) {
		for (e = u->crontab; e != NULL; e = e->next) {
			if (e->flags & WHEN_REBOOT)
				job_add(e, u);
		}
	}
	(void) job_runqueue();
}

static void
cron_tick(cron_db *db) {
	struct tm *tm = localtime(&TargetTime);
	int minute, hour, dom, month, dow;
	user *u;
	entry *e;

	/* make 0-based values out of these so we can use them as indicies
	 */
	minute = tm->tm_min -FIRST_MINUTE;
	hour = tm->tm_hour -FIRST_HOUR;
	dom = tm->tm_mday -FIRST_DOM;
	month = tm->tm_mon +1 /* 0..11 -> 1..12 */ -FIRST_MONTH;
	dow = tm->tm_wday -FIRST_DOW;

	Debug(DSCH, ("[%ld] tick(%d,%d,%d,%d,%d)\n",
		     (long)getpid(), minute, hour, dom, month, dow))

	/* the dom/dow situation is odd.  '* * 1,15 * Sun' will run on the
	 * first and fifteenth AND every Sunday;  '* * * * Sun' will run *only*
	 * on Sundays;  '* * 1,15 * *' will run *only* the 1st and 15th.  this
	 * is why we keep 'e->dow_star' and 'e->dom_star'.  yes, it's bizarre.
	 * like many bizarre things, it's the standard.
	 */
	for (u = db->head; u != NULL; u = u->next) {
		for (e = u->crontab; e != NULL; e = e->next) {
			Debug(DSCH|DEXT, ("user [%s:%ld:%ld:...] cmd=\"%s\"\n",
					  env_get("LOGNAME", e->envp),
					  (long)e->uid, (long)e->gid, e->cmd))
			if (bit_test(e->minute, minute) &&
			    bit_test(e->hour, hour) &&
			    bit_test(e->month, month) &&
			    ( ((e->flags & DOM_STAR) || (e->flags & DOW_STAR))
			      ? (bit_test(e->dow,dow) && bit_test(e->dom,dom))
			      : (bit_test(e->dow,dow) || bit_test(e->dom,dom))
			    )
			   )
				job_add(e, u);
		}
	}
}

/* the task here is to figure out how long it's going to be until :00 of the
 * following minute and initialize TargetTime to this value.  TargetTime
 * will subsequently slide 60 seconds at a time, with correction applied
 * implicitly in cron_sleep().  it would be nice to let cron execute in
 * the "current minute" before going to sleep, but by restarting cron you
 * could then get it to execute a given minute's jobs more than once.
 * instead we have the chance of missing a minute's jobs completely, but
 * that's something sysadmin's know to expect what with crashing computers..
 */
static void
cron_sync(void) {
 	struct tm *tm;

	TargetTime = time((time_t*)0);
	tm = localtime(&TargetTime);
	TargetTime += (60 - tm->tm_sec);
}

static void
cron_sleep(void) {
	int seconds_to_wait;

	do {
		seconds_to_wait = (int) (TargetTime - time((time_t*)0));
		Debug(DSCH, ("[%ld] TargetTime=%ld, sec-to-wait=%d\n",
			     (long)getpid(), (long)TargetTime,
			     seconds_to_wait))

		/* if we intend to sleep, this means that it's finally
		 * time to empty the job queue (execute it).
		 *
		 * if we run any jobs, we'll probably screw up our timing,
		 * so go recompute.
		 *
		 * note that we depend here on the left-to-right nature
		 * of &&, and the short-circuiting.
		 */
	} while (seconds_to_wait > 0 && job_runqueue());

	while (seconds_to_wait > 0) {
		Debug(DSCH, ("[%ld] sleeping for %d seconds\n",
			     (long)getpid(), seconds_to_wait))
		seconds_to_wait = (int) sleep((unsigned int) seconds_to_wait);
	}
}

static void
sigchld_handler(int x) {
	WAIT_T waiter;
	PID_T pid;

	for (;;) {
		pid = waitpid(-1, &waiter, WNOHANG);
		switch (pid) {
		case -1:
			Debug(DPROC,
			      ("[%ld] sigchld...no children\n",
			       (long)getpid()))
			return;
		case 0:
			Debug(DPROC,
			      ("[%ld] sigchld...no dead kids\n",
			       (long)getpid()))
			return;
		default:
			Debug(DPROC,
			      ("[%ld] sigchld...pid #%ld died, stat=%d\n",
			       (long)getpid(), (long)pid, WEXITSTATUS(waiter)))
		}
	}
}

static void
sighup_arm() {
	struct sigaction sact;

	sact.sa_handler = sighup_handler;
	sigemptyset(&sact.sa_mask);
	sigaddset(&sact.sa_mask, SIGCHLD);
	sact.sa_flags = 0;
# ifdef SA_RESTART
	sact.sa_flags |= SA_RESTART;
# endif
	sigaction(SIGHUP, &sact, NULL);
}

static void
sighup_handler(int x) {
	log_close();
#ifdef ATT
	sighup_arm();
#endif
}

static void
parse_args(int argc, char *argv[]) {
	int argch;

	while (EOF != (argch = getopt(argc, argv, "x:"))) {
		switch (argch) {
		default:
			usage();
		case 'x':
			if (!set_debug_flags(optarg))
				usage();
			break;
		}
	}
}
