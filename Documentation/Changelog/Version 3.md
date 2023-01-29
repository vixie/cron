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

- The `crontab` command now conforms to `POSIX 1003.2`.

	This means that when you install it, if you have any <br>
	`crontab` command lines floating around in shell <br>
	scripts, such as `/etc/rc` or `/etc/rc.local`, you <br>
	will need to change them.

- I have integrated several changes made by **BSDi** for <br>
	their `BSD/386`	operating system; these were offered <br>
	to me before I started consulting for them, so it is <br>
	safe to say that they were intended for publication.

	The name of the daemon has changed: <br>
	 `crond`  🠖  `cron`  

	*This was done for compatibility with ` BSD 4.3`.*

	Another change made for the same reason is the ability <br>
	to read in an `/etc/crontab` file which has an extra field <br>
	in each entry, between the time fields and the command.

	This field is a user name, and it permits the `/etc/crontab` <br>
	command to contain commands which are to be run by <br>
	any user on the system.

	`/etc/crontab` is not 'installed' via the crontab(1) command; <br>
	it is automatically read at startup time and it will be reread <br>
	whenever it changes.

- Added `-e` option to `crontab`.

	*Nine people also sent me diffs to add this option,* <br>
	*but I had already implemented it on my own.*

	I actually released an interim version, `V2.2` I think, for <br>
	limited testing, and got a chance to fix a bad security <br>
	bug in the `-e` option thanks to **XXX**.

- The daemon used to be extraordinarily <br>
	sloppy in its use of file descriptors.

	A heck of a lot of them were left open in spawned jobs, <br>
	which caused problems for the daemon and also caused <br>
	problems with the spawned jobs if they were  shell scripts <br>
	since `sh` and `csh` have traditionally used hidden file <br>
	descriptors to pass information to sub-shells, and Cron <br>
	was causing them to think they were sub-shells.

	If you had trouble with `sh` or `csh` scripts in V2, <br>
	chances are good that V3 will fix your problems.

- About a dozen people have reminded me that <br>
	I forgot to initialize`crontab_fd` in database.c.

	**Keith Cantrell** was the first, so he gets the point.

- **Steve Simmons** reminded me that once an account <br>
	has been deleted from the system, `crontab -u USER -d` <br>
	will not work.

	My solution is to suggest to all of you that before <br>
	you delete a user's account, you first delete that <br>
	user's crontab file if any.

	From cron's point of view, usernames can <br>
	never be treated as arbitrary strings.

	Either they are valid user names, or they are not.

	I will not make an exception for the `-d` case, <br>
	for security reasons that I consider reasonable.

	It is trivial for a root user to delete <br>
	the entry by hand if necessary.

- **Dan O'Neil** reminded me that I <br>
	forgot to reset `log_fd` in `misc.c`.

	A lot of others also reminded me <br>
	of this, but Dan gets the point.

	I didn't fix it there, since the real bug was <br>
	that it should have been open in the parent.

- **Peter Kabal** reminded me that I forgot to <br>
	`#ifdef DEBUGGING` some code in `misc.c`.

- **Hans Trompert** actually told me first, but <br>
	**Peter** sent the patch so he gets the point.

- **Russell Nelson** told me that I'd forgotten <br>
	to `#include <syslog.h>` in `misc.c`, which <br>
	explains why a lot of other people complained <br>
	that it wasn't using syslog even when they <br>
	configured it that way :-).

	**Steve Simmons** told me first, <br>
	though, so he gets the point.

- An interim version of the daemon tried to `stat` <br>
	every file before executing it; this turned out to <br>
	be a horribly bad idea since finding the name <br>
	of a file from a shell command is a hard job <br>
	(that's why we have shells, right?)

	I removed this bogus code.

	**Dave Burgess** gets the point.

- **Dennis R. Conley** sent a suggestion for **MMDF** systems, <br>
	which I've added to the comments in `cron.h`.

- **Mike Heisler** noted that I use comments in the CONVERSION <br>
	file which are documented as illegal in the man pages.

	Thanks, Mike.

- **Irving Wolfe** sent me some very cheerful changes for <br>
	a **NeXT** system, but I consider the system itself broken <br>
	and I can't bring myself to `#ifdef` for something as <br>
	screwed up as this system seems to be.

	However, various others did send me smaller patches <br>
	which appear to have cause cron to build and run <br>
	correctly on (the latest) **NeXT** machines, with or <br>
	without the `-posix` CFLAG.

	**Irving** also asked for a per-job `MAILTO`, and this was <br>
	finally added later when I integrated the `BSD/386` <br>
	changes contributed by **BSDi**, and generalized some <br>
	of the parsing.

- Lots of folks complained that the auto-generated <br>
	`Date:` header wasn't in **ARPA** format.

	I didn't understand this -- either folks will use **Sendmail** <br>
	and not generate a `Date:` at all (since Sendmail will do it), <br>
	or folks will use something other than Sendmail which <br>
	won't care about `Date:` formats.

	But I've 'fixed' it anyway...

- Several people suggested that `*` <br>
	should be able to take a `/step`.

	One person suggested that `N/step` ought to mean <br>
	`N-last/step`, but that's stretching things a bit far.

	`*/step` seems quite intuitive to me, so I've added it.

	**Colin Plumb** sent in the first and <br>
	most polite request for this feature.

- As with every release of **Cron**, `BIND`, and seemingly <br>
	everything else I do, one user stands out with the <br>
	most critical but also the most useful analysis.

- **Cron** V3's high score belongs to **Peter Holzer**, who sent <br>
	in the nicest looking patch for the `%` interpretation <br>
	problem and also helped me understand a tricky bit <br>
	of badness in the `log_fd` problem.

- `agulbra@flode.nvg.unit.no` wins the honors for being <br>
	the first to point out the nasty security hole in `crontab -r`.
	
	'Nuff said.

- Several folks pointed out that `log_it()` <br>
	needed to exist even if logging was disabled.

	Some day I will create a tool that will compile a subsystem <br>
	with every possible combination and permutation of `#ifdef` <br>
	options, but meanwhile thanks to everybody.

- `job_runqueue()` was using storage after freeing it, since **Jordan** <br>
	told me back in `1983` that C let you do that, and I believed him in <br>
	`1986` when I wrote all this junk.

	Linux was the first to die from this error, and the Linux people sent <br>
	me the most amazing, um, collection of patches for this problem.

	Thanks for all the fish.

- **Jeremy Bettis** reminded me that `popen()` isn't safe.

- I grabbed **Ken Arnold's** version of `popen/pclose` <br>
	from the ftpd and hacked it to taste.

	We're safe now, from this at least.

- **Branko Lankester** sent me a very timely and helpful fix for a <br>
	looming security problem in my `crontab -e` implementation.

<br>
<br>
