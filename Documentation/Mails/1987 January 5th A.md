
<!-- From ptsfa!hoptoad!hugh Mon Jan  5 10:26:46 1987 -->

**Date:** 
<kbd>1987 January 5th</kbd> 
<kbd>Monday</kbd> 
<kbd>01:22:17 PST</kbd> <br>
**From:** 
<kbd>hoptoad</kbd> 
<kbd>hugh (Hugh Daniel)</kbd>  <br>
**To:** 
<kbd>ptsfa</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- Status: RO -->

### Message

> Hi, I do have a BIG one that I would like.
>
> I want to log ALL output from command <br>
> lines into a file for each line.
>
> Thus I might have a chance of finding <br>
> out why my crontab entry did not work.
>
> This would seem to work best if done by cron, as it <br>
> is now I have a google of shell scripts laying about <br>
> just to put the error output where I can see it.

### Reply

> My cron (and the SysV cron) will send mail to the <br>
> owner of the particular crontab file if a command <br>
> generates any output on stdout or stderr.
>
> This can be irritating, but if you write a script such <br>
> that any output means a problem occurred, you <br>
> can avoid most logfile needs, and not generate <br>
> mail except in unforeseen circumstances.