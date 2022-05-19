
<!-- From qantel!hplabs!ucbvax!mwm@violet.berkeley.edu Tue Jan  6 21:24:48 1987 -->

**Date:** 
<kbd>1987 January 4th</kbd> 
<kbd>Sunday</kbd> 
<kbd>00:42:35 PST</kbd> <br>
**From:** 
<kbd>Mike Meyer <mwm@violet.berkeley.edu></kbd>  <br>
**To:** 
<kbd>hplabs</kbd> 
<kbd>qantel</kbd> 
<kbd>vixie</kbd> 
<kbd>paul (Paul Vixie Esq)</kbd> <br>

<!-- Status: RO -->

*Discussion of RMS/FSF, and mwm's GNU Cron deleted*

### Message

> Oh, yeah - here are the extensions on my cron:
>
> 1) Sunday is both day 0 and day 7, so it <br>
> complies with both SysV and BSD cron.

### Reply

> Good idea.
> I did it too, thanks for informing me.

### Message

> 2) At is integrated into the cron.
>   
>   Instead of atrun to scan the /usr/spool/at directory, <br>
>   at files are put into the /usr/lib/cron directory along <br>
>   with users cron files, and cron fabricates a line from <br>
>   a crontab file to run them.
>
>   This is considered a major win by all who use it.

### Reply

> I don't use 'at', and my cron doesn't do anything with it.
>
> To run 'at', I use 'atrun' the same way the current BSD cron does.
>
> My crontab files are in /usr/spool/cron/crontabs, <br>
> in the SysV tradition -- not in /usr/lib/cron.
>
> This is a configuration parameter, of course.

### Message

> There are two known restrictions:
>
> 1) I don't support any of the SysV security hooks.
> 
> I don't have a use for them, and <br>
> RMS didn't like the idea at all :-).

### Reply

> This means cron.allow and cron.deny.
>
> I plan to support them, as they've been quite <br>
> helpful at various HPUX sites I've administered.

### Message

> 2) Cron expects to be able to create files <br>
> with names longer than 14 characters, <br>
> which makes it hard to run on SysV.
>
> At least one person was working on a <br>
> port, but I don't know how it's going.
>
> That might make for a good reason <br>
> for releasing yours, right there.

### Reply

> If someone has SysV (with the 14-character limit), <br>
> they probably won't want my cron, since it doesn't <br>
> add much to the standard version <br>
> (which they may have support for).
>
> My cron is not currently portable to non-BSD systems, <br>
> since it relies on interval timers (I needed to sleep for <br>
> intervals more granular than seconds alone would allow).
>
> The port would be trivial, and I will <br>
> do it if a lot of people ask for it...

### Message

> Oh, yeah - I'm going to see about getting this <br>
> cron integrated into the next 4BSD release.

### Reply

> How does one go about this?
> 
> I have a few nifty gadgets I'd like to <br>
> contribute, this cron being one of them...

*More FSF/GNU discussion deleted*