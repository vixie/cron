
<!-- From ptsfa!lll-crg!ames!acornrc!bob Wed Dec 31 10:07:08 1986 -->

**Date:** 
<kbd>1986 December 31</kbd> 
<kbd>Wednesday</kbd> 
<kbd>08:59:31 PST</kbd> <br>
**From:** 
<kbd>lll-crg</kbd> 
<kbd>ames</kbd> 
<kbd>acornrc</kbd> 
<kbd>bob (Bob Weissman)</kbd> <br>
**To:** 
<kbd>ptsfa</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- **Status:** `RO` -->

### Message

> Sure, here's a suggestion:
>
> I'd like to be able to run a program, say, every two hours. <br>
> Current cron requires me to write <br>
>
> 0,2,4,6,8,10,12,14,16,18,20,22 
> 
> in the hours field.
>
> How about a notation to handle this more elegantly?

### Reply

> Okay, I've allowed 0-22/2 as a means of handling this.
>
> The time specification for my cron is as follows:
>
>    specification = range {"," range} <br>
>    range = (start "-" finish ["/" step]) | single-unit
>
> This allows "1,3,5-7", which the current cron doesn't <br>
> (it won't do a range inside a list), and handles your specific need.