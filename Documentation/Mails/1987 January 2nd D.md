<!-- From qantel!hplabs!ames!ut-sally!ut-ngp!melpad!bigtex!james Tue Jan  6 21:24:57 1987 -->

<!-- Posted-Date: Fri, 2 Jan 87 19:26:16 est -->

**Date:** 
<kbd>1987 January 2nd</kbd> 
<kbd>Friday</kbd> 
<kbd>19:26:16 EST</kbd> <br>
**From:** 
<kbd>hplabs</kbd> 
<kbd>ames</kbd> 
<kbd>ut-sally</kbd> 
<kbd>ut-ngp</kbd> 
<kbd>bigtex</kbd> 
<kbd>james</kbd>  <br>
**To:** 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- Status: RO -->

### Message

> Yes!!! <br>
> There are several critical failures in System V cron...
>
> 1. Pass all variables in cron's environment into the <br>
>   environment of things cron starts up, or at least <br>
>   into the crontab entries started up (at jobs will <br>
>   inherit the environment of the user).
>
>   If nothing else it is critically important <br>
>   that the TZ variable be passed on.
>
>   PATH should be passed on too.
>
>   Basically, passing environment values allows <br>
>   one to design a standard environment with <br>
>   TZ and PATH and have that run by everything.
>
>   If anyone tells you this is no big deal, consider <br>
>   what happens when uucico is started by cron in <br>
>   CA to make a long distance phone link...
>
>   Unless the administrator is really on his/her toes, <br>
>   calls scheduled at 5pm will really go at two in the <br>
>   afternoon, needlessly incurring huge phone bills, <br>
>   all because System V refuses to pass the TZ from <br>
>   its environment down.
>
>   There are work arounds, but only <br>
>   putting it in cron will really work.
>
>   This is not a security hole.

### Reply

> delete TERM and TERMCAP; modify HOME, USER, <br>
> and CWD; pass TZ and PATH through undisturbed.
>
> any other requests out there?
>
> BSD doesn't have this problem -- TZ is passed <br>
> right on through if you define it in the shell <br>
> before starting my cron daemon.
>
> However, the BSD I'm running this on <br>
> doesn't need TZ to be defined anyway...
>
> The default in the kernel has been just fine so far...  
>
> But just the same, if/when I port to SysV (I guess <br>
> I really should), I'll make sure this works right.
>
> I guess I've been spoiled.
>
> HPUX is SysV-based, and I never had a <br>
> problem with cron and TZ when I used it.

### Message

> 2. A way to avoid logging stuff in /usr/lib/cron/log.
> 
>   I have a cron entry run uudemon.hr every 10 minutes. <br>
>   This is 144 times/day.
> 
>   Each run generates three lines of text, for a <br>
>   total of 432 lines of text I don't want to see.
> 
>   Obviously this should be optional, but it would be <br>
>   nice if there were a way to flag an entry so nice it<br>
>   wasn't logged at all unless there was an error.

### Reply

> I don't know nothin' 'bout no /usr/lib/cron/log.
> 
> What is this file?
>
> I don't see any reason to create log entries, <br>
> given the mail-the-output behaviour.
>
> Opinions, anyone?

### Message

> I will come up with other ideas no doubt, <br>
> but I can always implement them myself.

### Reply

> That's what I like about PD software.
> 
> Please send me the diffs!

### Message

> The other problem you have is making <br>
> sure you can run standard crontabs.
>
> I would suggest something like this: <br>
>
> if the command part of the entry starts with <br>
> an unescaped -, then flags and options follow <br>
> immediately thereafter.
>
> As in:
>
> ```crontab
> 2,12,22,32,42,52 * * * * -q /usr/lib/uucp/uudemon.hr
> ```
>
> This could mean do not log the uudemon.hr <br>
> run unless there is a problem of some kind.
> 
> This is probably safe as not many filenames <br>
> start with "-", and those that do are already <br>
> a problem for people.

### Reply

> Since I don't plan on supporting /usr/lib/cron/log <br>
> in ANY form unless many people request it, I won't <br>
> be needing -q as you've defined it.
>
> I could use something like this to avoid sending <br>
> mail on errors, for the occasional script that you <br>
> don't want to bullet-proof.
>
> The compatibility issue is CRITICAL.
> 
> The 4.3BSD crontab format is a crime against the <br>
> whole philosophy of Unix(TM), in my opinion.

### Message

> One other minor thing to consider is the ulimit:
>
> can different users get different <br>
> ulimits for their crontab entries?

### Reply

> Boy I'm ignorant today.
> 
> What's a ulimit, and what should <br>
> I do with it in a crontab?
> 
> Suggestions, enlightenment, etc ??