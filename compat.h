/* Copyright 1993,1994 by Paul Vixie
 * All rights reserved
 *
 * Distribute freely, except: don't remove my name from the source or
 * documentation (don't take credit for my work), mark your changes (don't
 * get me blamed for your possible bugs), don't alter or remove this
 * notice.  May be sold if buildable source is provided to buyer.  No
 * warrantee of any kind, express or implied, is included with this
 * software; use at your own risk, responsibility for damages (if any) to
 * anyone resulting from the use of this software rests entirely with the
 * user.
 *
 * Send bug reports, bug fixes, enhancements, requests, flames, etc., and
 * I'll try to keep a version up to date.  I can be reached as follows:
 * Paul Vixie          <paul@vix.com>          uunet!decwrl!vixie!paul
 */

/*
 * $Id: compat.h,v 1.1 1996/12/16 19:39:48 halley Exp $
 */

#ifndef __P
# ifdef __STDC__
#  define __P(x) x
# else
#  define __P(x) ()
#  define const
# endif
#endif

#if defined(UNIXPC) || defined(unixpc)
# define UNIXPC 1
# define ATT 1
#endif

#if defined(hpux) || defined(_hpux) || defined(__hpux)
# define HPUX 1
# define seteuid(e) setresuid(-1,e,-1)
# define setreuid(r,e)	setresuid(r,e,-1)
#endif

#if defined(_IBMR2)
# define AIX 1
#endif

#if defined(__convex__)
# define CONVEX 1
#endif

#if defined(sgi) || defined(_sgi) || defined(__sgi)
# define IRIX 1
/* IRIX 4 hdrs are broken: one cannot #include both <stdio.h>
 * and <stdlib.h> because they disagree on system(), perror().
 * Therefore we must zap the "const" keyword BEFORE including
 * either of them.
 */
# define const
#endif

#if defined(_UNICOS)
# define UNICOS 1
#endif

#ifndef POSIX
# if (BSD >= 199103) || defined(__linux) || defined(ultrix) || defined(AIX) ||\
	defined(HPUX) || defined(CONVEX) || defined(IRIX)
#  define POSIX
# endif
#endif

#ifndef BSD
# if defined(ultrix)
#  define BSD 198902
# endif
#endif

/*****************************************************************/

#if !defined(BSD) && !defined(HPUX) && !defined(CONVEX) && !defined(__linux)
# define NEED_VFORK
#endif

#if (!defined(BSD) || (BSD < 198902)) && !defined(__linux) && \
	!defined(IRIX) && !defined(NeXT) && !defined(HPUX)
# define NEED_STRCASECMP
#endif

#if (!defined(BSD) || (BSD < 198911)) && !defined(__linux) &&\
	!defined(IRIX) && !defined(UNICOS) && !defined(HPUX)
# define NEED_STRDUP
#endif

#if (!defined(BSD) || (BSD < 198911)) && !defined(POSIX) && !defined(NeXT)
# define NEED_STRERROR
#endif

#if defined(HPUX) || defined(AIX) || defined(UNIXPC)
# define NEED_FLOCK
#endif

#ifndef POSIX
# define NEED_SETSID
#endif

#if !defined(BSD) && !defined(__linux)
# define NEED_GETDTABLESIZE
#endif

#if (BSD >= 199103)
# define HAVE_SAVED_UIDS
#endif

#if defined(COHERENT)
# define TZNAME_ALREADY_DEFINED
#endif

#if defined(COHERENT)
# define MY_UID(pw) pw->pw_uid
# define MY_GID(pw) pw->pw_gid
#else
# define MY_UID(pw) getuid()
# define MY_GID(pw) getgid()
#endif

#if !defined(ATT) && !defined(__linux) && !defined(IRIX) \
	&& !defined(UNICOS) && !defined(COHERENT)
# define USE_SIGCHLD
#endif

#if !defined(AIX) && !defined(UNICOS)
# define SYS_TIME_H 1
#else
# define SYS_TIME_H 0
#endif

#if defined(BSD) && !defined(POSIX)
# define USE_UTIMES
#endif

#if defined(AIX) || defined(HPUX) || defined(IRIX)
# define NEED_SETENV
#endif

#if !defined(UNICOS) && !defined(UNIXPC) && !defined(COHERENT)
# define HAS_FCHOWN
#endif

#if !defined(UNICOS) && !defined(UNIXPC) && !defined(COHERENT)
# define HAS_FCHMOD
#endif

#if defined(COHERENT)
# define ANONPTR char *
#else
# define ANONPTR void *
#endif

#if defined(COHERENT)
#include <sys/param.h>
#include <sys/utsname.h>
#define bzero(b,s) memset((b),0,(s))
#define setreuid setuid
#define WAIT_IS_INT 1
#define NEED_GETHOSTNAME
#define NEED_FLOCK
#define EWOULDBLOCK EAGAIN
#define _POSIX_OPEN_MAX _NFILE
#define NEED_GETDTABLESIZE
#define _PATH_TMP "/usr/tmp"
#define RENAME_ISNT_ATOMIC
#endif
