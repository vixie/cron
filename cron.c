/*
 * Copyright (c) 1988,1990,1993,1994,2021 by Paul Vixie ("VIXIE")
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1997,2000 by Internet Software Consortium, Inc.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND VIXIE DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL VIXIE BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#if !defined(lint) && !defined(LINT)
static char rcsid[] = "$Id: cron.c,v 1.12 2004/01/23 18:56:42 vixie Exp $";
#endif

#define	MAIN_PROGRAM

#include "cron.h"

enum timejump { negative, small, medium, large };

static	void	usage(void),
		run_reboot_jobs(cron_db *),
		find_jobs(int, cron_db *, int, int),
		set_time(int),
		cron_sleep(int),
		sigchld_handler(int),
		sighup_handler(int),
		sigchld_reaper(void),
		quit(int),
		parse_args(int c, char *v[]);

static	volatile sig_atomic_t	got_sighup, got_sigchld;
static	int			timeRunning, virtualTime, clockTime;
static	long			GMToff;

static void
usage(void) {
	const char **dflags;

	fprintf(stderr, "usage:  %s [-n] [-x [", ProgramName);
	for (dflags = DebugFlagNames; *dflags; dflags++)
		fprintf(stderr, "%s%s", *dflags, dflags[1] ? "," : "]");
	fprintf(stderr, "]\n");
	exit(ERROR_EXIT);
}

int
main(int argc, char *argv[]) {
	struct sigaction sact;
	cron_db	database;
	int fd;

	ProgramName = argv[0];

	setlocale(LC_ALL, "");

#if defined(BSD)
	setlinebuf(stdout);
	setlinebuf(stderr);
#endif

	NoFork = 0;
	parse_args(argc, argv);

	bzero((char *)&sact, sizeof sact);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
#ifdef SA_RESTART
	sact.sa_flags |= SA_RESTART;
#endif
	sact.sa_handler = sigchld_handler;
	(void) sigaction(SIGCHLD, &sact, NULL);
	sact.sa_handler = sighup_handler;
	(void) sigaction(SIGHUP, &sact, NULL);
	sact.sa_handler = quit;
	(void) sigaction(SIGINT, &sact, NULL);
	(void) sigaction(SIGTERM, &sact, NULL);

	acquire_daemonlock(0);
	set_cron_uid();
	set_cron_cwd();

	if (putenv("PATH="_PATH_DEFPATH) < 0) {
		log_it("CRON", getpid(), "DEATH", "can't malloc");
		exit(1);
	}

	/* if there are no debug flags turned on, fork as a daemon should.
	 */
	if (DebugFlags) {
#if DEBUGGING
		(void) fprintf(stderr, "[%ld] cron started\n", (long)getpid());
#endif
	} else if (NoFork == 0) {
		switch (fork()) {
		case -1:
			log_it("CRON",getpid(),"DEATH","can't fork");
			exit(0);
			break;
		case 0:
			/* child process */
			(void) setsid();
			if ((fd = open(_PATH_DEVNULL, O_RDWR, 0)) >= 0) {
				(void) dup2(fd, STDIN);
				(void) dup2(fd, STDOUT);
				(void) dup2(fd, STDERR);
				if (fd != STDERR)
					(void) close(fd);
			}
			log_it("CRON",getpid(),"STARTUP",CRON_VERSION);
			break;
		default:
			/* parent process should just die */
			_exit(0);
		}
	}

	acquire_daemonlock(0);
	database.head = NULL;
	database.tail = NULL;
	database.mtim = ts_zero;
	load_database(&database);
	set_time(TRUE);
	run_reboot_jobs(&database);
	timeRunning = virtualTime = clockTime;

	/*
	 * Too many clocks, not enough time (Al. Einstein)
	 * These clocks are in minutes since the epoch, adjusted for timezone.
	 * virtualTime: is the time it *would* be if we woke up
	 * promptly and nobody ever changed the clock. It is
	 * monotonically increasing... unless a timejump happens.
	 * At the top of the loop, all jobs for 'virtualTime' have run.
	 * timeRunning: is the time we last awakened.
	 * clockTime: is the time when set_time was last called.
	 */
	while (TRUE) {
		int timeDiff;
		enum timejump wakeupKind;

		/* ... wait for the time (in minutes) to change ... */
		do {
			cron_sleep(timeRunning + 1);
			set_time(FALSE);
		} while (clockTime == timeRunning);
		timeRunning = clockTime;

		/*
		 * Calculate how the current time differs from our virtual
		 * clock.  Classify the change into one of 4 cases.
		 */
		timeDiff = timeRunning - virtualTime;

		/* shortcut for the most common case */
		if (timeDiff == 1) {
			virtualTime = timeRunning;
			find_jobs(virtualTime, &database, TRUE, TRUE);
		} else {
			if (timeDiff > (3*MINUTE_COUNT) ||
			    timeDiff < -(3*MINUTE_COUNT))
				wakeupKind = large;
			else if (timeDiff > 5)
				wakeupKind = medium;
			else if (timeDiff > 0)
				wakeupKind = small;
			else
				wakeupKind = negative;

			switch (wakeupKind) {
			case small:
				/*
				 * case 1: timeDiff is a small positive number
				 * (wokeup late) run jobs for each virtual
				 * minute until caught up.
				 */
				Debug(DSCH, ("[%ld], normal case %d minutes to go\n",
				    (long)getpid(), timeDiff))
				do {
					if (job_runqueue())
						sleep(10);
					virtualTime++;
					find_jobs(virtualTime, &database,
					    TRUE, TRUE);
				} while (virtualTime < timeRunning);
				break;

			case medium:
				/*
				 * case 2: timeDiff is a medium-sized positive
				 * number, for example because we went to DST
				 * run wildcard jobs once, then run any
				 * fixed-time jobs that would otherwise be
				 * skipped if we use up our minute (possible,
				 * if there are a lot of jobs to run) go
				 * around the loop again so that wildcard jobs
				 * have a chance to run, and we do our
				 * housekeeping.
				 */
				Debug(DSCH, ("[%ld], DST begins %d minutes to go\n",
				    (long)getpid(), timeDiff))
				/* run wildcard jobs for current minute */
				find_jobs(timeRunning, &database, TRUE, FALSE);
	
				/* run fixed-time jobs for each minute missed */
				do {
					if (job_runqueue())
						sleep(10);
					virtualTime++;
					find_jobs(virtualTime, &database,
					    FALSE, TRUE);
					set_time(FALSE);
				} while (virtualTime< timeRunning &&
				    clockTime == timeRunning);
				break;
	
			case negative:
				/*
				 * case 3: timeDiff is a small or medium-sized
				 * negative num, eg. because of DST ending.
				 * Just run the wildcard jobs. The fixed-time
				 * jobs probably have already run, and should
				 * not be repeated.  Virtual time does not
				 * change until we are caught up.
				 */
				Debug(DSCH, ("[%ld], DST ends %d minutes to go\n",
				    (long)getpid(), timeDiff))
				find_jobs(timeRunning, &database, TRUE, FALSE);
				break;
			default:
				/*
				 * other: time has changed a *lot*,
				 * jump virtual time, and run everything
				 */
				Debug(DSCH, ("[%ld], clock jumped\n",
				    (long)getpid()))
				virtualTime = timeRunning;
				find_jobs(timeRunning, &database, TRUE, TRUE);
			}
		}

		/* Jobs to be run (if any) are loaded; clear the queue. */
		job_runqueue();

		/* Check to see if we received a signal while running jobs. */
		if (got_sighup) {
			got_sighup = 0;
			log_close();
		}
		if (got_sigchld) {
			got_sigchld = 0;
			sigchld_reaper();
		}
		load_database(&database);
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
find_jobs(int vtime, cron_db *db, int doWild, int doNonWild) {
	time_t virtualSecond  = vtime * SECONDS_PER_MINUTE;
	struct tm *tm = gmtime(&virtualSecond);
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

	Debug(DSCH, ("[%ld] tick(%d,%d,%d,%d,%d) %s %s\n",
		     (long)getpid(), minute, hour, dom, month, dow,
		     doWild?" ":"No wildcard",doNonWild?" ":"Wildcard only"))

	/* the dom/dow situation is odd.  '* * 1,15 * Sun' will run on the
	 * first and fifteenth AND every Sunday;  '* * * * Sun' will run *only*
	 * on Sundays;  '* * 1,15 * *' will run *only* the 1st and 15th.  this
	 * is why we keep 'e->dow_star' and 'e->dom_star'.  yes, it's bizarre.
	 * like many bizarre things, it's the standard.
	 */
	for (u = db->head; u != NULL; u = u->next) {
		for (e = u->crontab; e != NULL; e = e->next) {
			Debug(DSCH|DEXT, ("user [%s:%ld:%ld:...] cmd=\"%s\"\n",
			    e->pwd->pw_name, (long)e->pwd->pw_uid,
			    (long)e->pwd->pw_gid, e->cmd))
			if (bit_test(e->minute, minute) &&
			    bit_test(e->hour, hour) &&
			    bit_test(e->month, month) &&
			    ( ((e->flags & DOM_STAR) || (e->flags & DOW_STAR))
			      ? (bit_test(e->dow,dow) && bit_test(e->dom,dom))
			      : (bit_test(e->dow,dow) || bit_test(e->dom,dom))
			    )
			   ) {
				if ((doNonWild &&
				    !(e->flags & (MIN_STAR|HR_STAR))) || 
				    (doWild && (e->flags & (MIN_STAR|HR_STAR))))
					job_add(e, u);
			}
		}
	}
}

/*
 * Set StartTime and clockTime to the current time.
 * These are used for computing what time it really is right now.
 * Note that clockTime is a unix wallclock time converted to minutes.
 */
static void
set_time(int initialize) {
	struct tm tm;
	static int isdst;

	StartTime = time(NULL);

	/* We adjust the time to GMT so we can catch DST changes. */
	tm = *localtime(&StartTime);
	if (initialize || tm.tm_isdst != isdst) {
		isdst = tm.tm_isdst;
		GMToff = get_gmtoff(&StartTime, &tm);
		Debug(DSCH, ("[%ld] GMToff=%ld\n",
		    (long)getpid(), (long)GMToff))
	}
	clockTime = (StartTime + GMToff) / (time_t)SECONDS_PER_MINUTE;
}

/*
 * Try to just hit the next minute.
 */
static void
cron_sleep(int target) {
	time_t t1, t2;
	int seconds_to_wait;

	t1 = time(NULL) + GMToff;
	seconds_to_wait = (int)(target * SECONDS_PER_MINUTE - t1) + 1;
	Debug(DSCH, ("[%ld] Target time=%ld, sec-to-wait=%d\n",
	    (long)getpid(), (long)target*SECONDS_PER_MINUTE, seconds_to_wait))

	while (seconds_to_wait > 0 && seconds_to_wait < 65) {
		sleep((unsigned int) seconds_to_wait);

		/*
		 * Check to see if we were interrupted by a signal.
		 * If so, service the signal(s) then continue sleeping
		 * where we left off.
		 */
		if (got_sighup) {
			got_sighup = 0;
			log_close();
		}
		if (got_sigchld) {
			got_sigchld = 0;
			sigchld_reaper();
		}
		t2 = time(NULL) + GMToff;
		seconds_to_wait -= (int)(t2 - t1);
		t1 = t2;
	}
}

static void
sighup_handler(int x) {
	got_sighup = 1;
}

static void
sigchld_handler(int x) {
	got_sigchld = 1;
}

static void
quit(int x) {
	(void) unlink(_PATH_CRON_PID);
	_exit(0);
}

static void
sigchld_reaper(void) {
	WAIT_T waiter;
	PID_T pid;

	do {
		pid = waitpid(-1, &waiter, WNOHANG);
		switch (pid) {
		case -1:
			if (errno == EINTR)
				continue;
			Debug(DPROC,
			      ("[%ld] sigchld...no children\n",
			       (long)getpid()))
			break;
		case 0:
			Debug(DPROC,
			      ("[%ld] sigchld...no dead kids\n",
			       (long)getpid()))
			break;
		default:
			Debug(DPROC,
			      ("[%ld] sigchld...pid #%ld died, stat=%d\n",
			       (long)getpid(), (long)pid, WEXITSTATUS(waiter)))
			break;
		}
	} while (pid > 0);
}

static void
parse_args(int argc, char *argv[]) {
	int argch;

	while (-1 != (argch = getopt(argc, argv, "nM:x:"))) {
		switch (argch) {
		default:
			usage();
		case 'x':
			if (!set_debug_flags(optarg))
				usage();
			break;
		case 'M':
			if (strlen(optarg) == 0)
				usage();
			Mailer = optarg;
			break;
		case 'n':
			NoFork = 1;
			break;
		}
	}
}
