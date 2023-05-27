<!-- From ptsfa!ames!seismo!ihnp4!lcc!richard Fri Jan 16 04:47:33 1987 -->

**Date:** 
<kbd>1987 January 16th</kbd> 
<kbd>Friday</kbd> 
<kbd>07:44:57 EST</kbd> <br>
**To:** 
<kbd>nike</kbd> 
<kbd>ptsfa</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- Status: RO -->

### Message

> The System V cron is nice, but <br>
> it has a few annoying features.
> 
> One is that its mail files will say that <br>
> the previous message is the output <br>
> of "one of your cron commands."
>
> I wish it would say WHICH cron commmand.

### Reply

> Done.
> 
> Also which shell, which user (useful when the <br>
> mail gets forwarded), which home directory, <br>
> and other useful crud.

### Message

> Another problem is with timezones.
>
> It is necessary to specify TZ=PST8PDT (or whatever) <br>
> when you invoke cron (from inittab, or /etc/rc) and <br>
> it is also necessary to add TZ=PST8PDT to each <br>
> crontab line which might need it.
>
> Cron should automatically export its idea of the "TZ" <br>
> to each invoked command, and it should be possible <br>
> to put a line in the crontab file which overrides that <br>
> for every command in the file (e.g., most users are <br>
> on EST, so cron is run with TZ=EST5EDT; but one user <br>
> is usually on PST and wants all of his cron commands <br>
> to run with TZ=PST8PDT).
>
> This might be extended to allow any environment <br>
> variable to be specified once for the whole crontab <br>
> file (e.g., PATH).

### Reply

> Well, since I run the user's shell, you could put this into .cshrc.
>
> generic environment-variable setting could be useful, though.
>
> Since I have to modify the environment anyway, I'll consider this.

### Message

> A log file might be a nice idea, but <br>
> the System V cron log is too verbose.
>
> I seem to remember that cron keeps it open, <br>
> too; so you can't even have something go and <br>
> periodically clean it out.

### Reply

> I don't do `/usr/lib/cron/log`.
>
> I wasn't aware of this file until <br>
> I got all these suggestions.
>
> Do people want this file? <br>
> Tell me!
