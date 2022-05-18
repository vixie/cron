
<!-- From ptsfa!ames!seismo!dgis!generous Thu Jan  1 07:33:17 1987 -->

**Date:** 
<kbd>1987 January 1st</kbd> 
<kbd>Thursday</kbd> 
<kbd>10:29:20</kbd> <br>
**From:** 
<kbd>ames</kbd> 
<kbd>seismo</kbd> 
<kbd>dgis</kbd> 
<kbd>generous (Curtis Generous)</kbd>  <br>
**To:** 
<kbd>nike</kbd> 
<kbd>ptsfa</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- **Status:** `RO` -->

### Paul

> One of the limitations of the present versions of <br>
> cron is the lack of the capability of specifying a <br>
> way to execute a command every n units of time.
>
> Here is a good example:
>
> ```src
> # Present method to start up uucico
> 02,12,22,32,42,52 * * * * 	exec /usr/lib/uucp/uucico -r1
>
>
># New method ?? (the ':' here is just one possibility for syntax)
>02:10 * * * *			exec /usr/lib/uucp/uucico -r1
>```
>
> This method would prove very helpful for those <br>
> programs that get started every few minutes, <br>
> making the entry long and not easily readable.
>
> The first number would specify the base time, <br>
> and the second number the repetition interval.

### Reply

> Good idea, but bob@acornrc beat you to it.
>
> I used '/' instead of ':'.
>
> This is my personal preference, and seems <br>
> intuitive when you think of the divide operator <br>
> in C... Does anyone have a preference?