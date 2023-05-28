/*
 * $Id: globals.h,v 1.10 2004/01/23 19:03:33 vixie Exp $
 */

/*
 * Copyright (c) 2021 by Paul Vixie ("VIXIE")
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

#ifdef MAIN_PROGRAM
# define XTRN
# define INIT(x) = x
#else
# define XTRN extern
# define INIT(x)
#endif

XTRN const char *copyright[]
#ifdef MAIN_PROGRAM
	= {
		"@(#) Vixie Cron",
		"@(#) Copyright 1988,1989,1990,1993,1994,2021 by Paul Vixie",
		"@(#) Copyright 1997,2000 by Internet Software Consortium, Inc.",
		"@(#) Copyright 2004 by Internet Systems Consortium, Inc.",
		"@(#) Copyright 2023 by Paul Vixie",
		"@(#) All rights reserved",
		NULL
	}
#endif
	;

XTRN const char *MonthNames[]
#ifdef MAIN_PROGRAM
	= {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		NULL
	}
#endif
	;

XTRN const char *DowNames[]
#ifdef MAIN_PROGRAM
	= {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun",
		NULL
	}
#endif
	;

XTRN char	*ProgramName INIT("amnesia");
XTRN int	LineNumber INIT(0);
XTRN time_t	StartTime INIT(0);
XTRN char	*Mailer INIT(NULL);
XTRN int	NoFork INIT(0);
XTRN const struct timespec ts_zero 
#ifdef MAIN_PROGRAM
= {.tv_sec = 0, .tv_nsec = 0}
#endif
;
#if DEBUGGING
XTRN int	DebugFlags INIT(0);
XTRN const char *DebugFlagNames[]
#ifdef MAIN_PROGRAM
	= {
		"ext", "sch", "proc", "pars", "load", "misc", "test", "bit",
		NULL
	}
#endif
	;
#else
#define	DebugFlags	0
#endif /* DEBUGGING */
