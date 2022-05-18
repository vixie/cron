
# Changelog

<br>

## Version 4

### 4.1

<kbd>January 2004</kbd>

### 4.0 

<kbd>November 2000</kbd>

### 4.0-b1

<kbd>September 7, 1997</kbd>

### V4 vs V3

- [ Security ]

	Check `setuid()` result.
	
	Reported by **Thomas Pollet**.

- [ Func ]

	Add `MAIL_FROMUSER` option.
	
	See `config.h` comments.
	
- [ Misc ]
	
	Megapatch from **tcmiller**
	
	(POSIX compliance, ..)
	
- [ Bug ]

	Fix stepsize `0` infinite loop.

- [ Evol ]

	`enum` version of **FreeBSD** <br>
	fix to `env-var` settings.
	
- [ Evol ]

	Changes `#12 - 17` from **tcmiller** 
	
	For **BSD** alignment.
	
- [ Feature ]

	Give cron a version number and display it.
	
- [ Bug ]

	Handle clock jumps 
	
	From FreeBSD Pull Request `24485`
	
- [ Feature ]

	Add `-n` to cron
	
	For nofork.
	
- [ Evol ]

	Merge in many changes <br>
	from **BSD** and **Linux**.
	
- [ Port ]

	Fixups for nextstep, plus a <br>
	syslog configuration bug.

<br>
<br>

## Version 3

### Patch 2

<kbd>12 Dec 1994</kbd>

- `gethostname()` now available in `compat.c`.

- Fixed various `flock()` problems.

- Fixed environment importing.

- `Coherent` now supported.


### 3.1

<kbd>Some time after 1993</kbd>

### 3.0 

<kbd>December 27, 1993</kbd>

### V3 vs V2

<kbd>1993 December 29</kbd>

The crontab command now conforms to POSIX 1003.2.  This means that when you
install it, if you have any "crontab" command lines floating around in shell
scripts (such as /etc/rc or /etc/rc.local), you will need to change them.

I have integrated several changes made by BSDi for their BSD/386 operating
system; these were offerred to me before I started consulting for them, so
it is safe to say that they were intended for publication.  Most notably,
the name of the cron daemon has changed from "crond" to "cron".  This was
done for compatibility with 4.3BSD.  Another change made for the same reason
is the ability to read in an /etc/crontab file which has an extra field in
each entry, between the time fields and the command.  This field is a user
name, and it permits the /etc/crontab command to contain commands which are
to be run by any user on the system.  /etc/crontab is not "installed" via
the crontab(1) command; it is automatically read at startup time and it will
be reread whenever it changes.

I also added a "-e" option to crontab(1).  Nine people also sent me diffs
to add this option, but I had already implemented it on my own.  I actually
released an interrim version (V2.2, I think) for limited testing, and got a
chance to fix a bad security bug in the "-e" option thanks to XXX.

The daemon used to be extraordinarily sloppy in its use of file descriptors.
A heck of a lot of them were left open in spawned jobs, which caused problems
for the daemon and also caused problems with the spawned jobs if they were 
shell scripts since "sh" and "csh" have traditionally used hidden file
descriptors to pass information to subshells, and cron was causing them to
think they were subshells.  If you had trouble with "sh" or "csh" scripts in
V2, chances are good that V3 will fix your problems.

About a dozen people have reminded me that I forgot to initialize
"crontab_fd" in database.c.  Keith Cantrell was the first, so he gets the
point.

Steve Simmons reminded me that once an account has been deleted from the
system, "crontab -u USER -d" will not work.  My solution is to suggest to
all of you that before you delete a user's account, you first delete that
user's crontab file if any.  From cron's point of view, usernames can never
be treated as arbitrary strings.  Either they are valid user names, or they
are not.  I will not make an exception for the "-d" case, for security
reasons that I consider reasonable.  It is trivial for a root user to delete
the entry by hand if necessary.

Dan O'Neil reminded me that I forgot to reset "log_fd" in misc.c.  A lot of
others also reminded me of this, but Dan gets the point.  I didn't fix it
there, since the real bug was that it should have been open in the parent.

Peter Kabal reminded me that I forgot to "#ifdef DEBUGGING" some code in
misc.c.  Hans Trompert actually told me first, but Peter sent the patch so
he gets the point.

Russell Nelson told me that I'd forgotten to "#include <syslog.h>" in misc.c,
which explains why a lot of other people complained that it wasn't using
syslog even when they configured it that way :-).  Steve Simmons told me
first, though, so he gets the point.

An interrim version of the daemon tried to "stat" every file before
executing it; this turned out to be a horribly bad idea since finding the
name of a file from a shell command is a hard job (that's why we have
shells, right?)  I removed this bogus code.  Dave Burgess gets the point.

Dennis R. Conley sent a suggestion for MMDF systems, which I've added to the
comments in cron.h.

Mike Heisler noted that I use comments in the CONVERSION file which are
documented as illegal in the man pages.  Thanks, Mike.

Irving Wolfe sent me some very cheerful changes for a NeXT system, but I
consider the system itself broken and I can't bring myself to #ifdef for
something as screwed up as this system seems to be.  However, various others
did send me smaller patches which appear to have cause cron to build and run
correctly on (the latest) NeXT machines, with or without the "-posix" CFLAG.
Irving also asked for a per-job MAILTO, and this was finally added later when
I integrated the BSD/386 changes contributed by BSDi, and generalized some of
the parsing.

Lots of folks complained that the autogenerated "Date:" header wasn't in
ARPA format.  I didn't understand this -- either folks will use Sendmail and
not generate a Date:  at all (since Sendmail will do it), or folks will use
something other than Sendmail which won't care about Date: formats.  But
I've "fixed" it anyway...

Several people suggested that "*" should be able to take a "/step".  One person
suggested that "N/step" ought to mean "N-last/step", but that's stretching things
a bit far.  "*/step" seems quite intuitive to me, so I've added it.  Colin Plumb
sent in the first and most polite request for this feature.

As with every release of Cron, BIND, and seemingly everything else I do, one
user stands out with the most critical but also the most useful analysis.
Cron V3's high score belongs to Peter Holzer, who sent in the nicest looking
patch for the "%" interpretation problem and also helped me understand a
tricky bit of badness in the "log_fd" problem.

agulbra@flode.nvg.unit.no wins the honors for being the first to point out the
nasty security hole in "crontab -r".  'Nuff said.

Several folks pointed out that log_it() needed to exist even if logging was
disabled.  Some day I will create a tool that will compile a subsystem with
every possible combination and permutation of #ifdef options, but meanwhile
thanks to everybody.

job_runqueue() was using storage after freeing it, since Jordan told me back
in 1983 that C let you do that, and I believed him in 1986 when I wrote all
this junk.  Linux was the first to die from this error, and the Linux people
sent me the most amazing, um, collection of patches for this problem.  Thanks
for all the fish.

Jeremy Bettis reminded me that popen() isn't safe.  I grabbed Ken Arnold's 
version of popen/pclose from the ftpd and hacked it to taste.  We're safe now,
from this at least.

Branko Lankester sent me a very timely and helpful fix for a looming security
problem in my "crontab -e" implementation.

<br>
<br>

## Version 2

### 2.2

<kbd>Some time in 1992</kbd>

### 2.1

<kbd>May 29, 1991</kbd>

### 2.0

<kbd>July 5, 1990</kbd>

### 2.0-beta

<kbd>December 9, 1988</kbd>

### V2 vs V1

<kbd>1988 February 8th</kbd>

Many changes were made in a rash of activity <br>
about six months ago, the exact list of which <br>
is no longer clear in my memory.

I know that V1 used a file called `POKECRON` in <br>
`/usr/spool/cron` to tell it that it was time to <br>
re-read all the crontab files.

V2 uses the `modtime` the `crontab` directory <br>
as a flag to check out the crontab files; those <br>
whose modtime has changed will be re-read, <br>
and the others left alone.

Note that the crontab(1) command will do a <br>
`utimes` call to make sure the `mtime` of the <br>
dir changes, since the filename / inode will <br>
often remain the same after a replacement <br>
and the mtime wouldn't change in that case.

<br>

#### <kbd>1988 February 8th</kbd>

- Environment variables strings can be longer:

	`100`  🠖  `1000`
	
	*This was needed for `PATH`* <br>
	*variables on some systems.*
	
	Thanks to **Toerless Eckert** for this idea.

<!-- E-mail: UUCP: ...pyramid!fauern!faui10!eckert -->

<br>

#### <kbd>1988 February 16th</kbd>

- Moved `/usr/spool/cron/crontabs` to `/usr/lib/cron/tabs`

- Added `allow` / `deny`

	⤷ `/usr/lib/cron/{allow,deny}`
	
	⤷ Since the **System V** naming for this depends on <br>
	`at` using the same directory, which would be stupid.
	
	*Hint: Use `/usr/{lib,spool}/at`*

<br>

#### <kbd>1988 February 22nd</kbd>

Use `getpwent()` to read `passwds` <br>and try to open each crontab.

                      🠗

Read the `spool` directory for crontabs <br>
& look each one up using `getpwnam()`.

<br>

#### <kbd>1988 December 9th</kbd>

- Now syncs to `00` after every minute

	⤷ Makes **Cron** predictable.
	
- Added logging to `/var/cron/log`.

<br>

#### <kbd>1990 April 14th</kbd>

*Actually, changes since December 1989*

- Fixed a number of bugs reported by **John Gilmore**.

- Added `syslog` per **Keith Bostic**.

- Added security features:

	Commands can only be run by, the owner <br>
	of / with write permission to, the crontab.

	*Not working well yet*


<br>
<br>

## Version 1

### 1.0

<kbd>May 6, 1987</kbd>


