
<!-- From ptsfa!dual!ucbvax!ihnp4!anvil!es!Robert_Toxen Mon Jan  5 13:08:46 1987 -->

**Date:** 
<kbd>1987 January 2nd</kbd> 
<kbd>Friday</kbd> 
<kbd>14:25:29 EST</kbd> <br>
**From:** 
<kbd>dual</kbd> 
<kbd>ucbvax</kbd> 
<kbd>ihnp4</kbd> 
<kbd>anvil</kbd> 
<kbd>es</kbd> 
<kbd>Robert_Toxen</kbd>  <br>
**To:** 
<kbd>anvil</kbd> 
<kbd>ihnp4</kbd> 
<kbd>ucbvax</kbd> 
<kbd>dual</kbd> 
<kbd>ptsfa</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- Status: RO -->

### Message

> Here are some suggestions:
> 1. Run it through the C preprocessor via "/lib/<whatever>".

### Reply

> hmmm. this seems of limited utility, and if you really <br>
> wanted to do it that way, you could do it yourself <br>
> (since users can write to their own crontab files).
>
> I'll add '-' (read stdin) to the crontab <br>
> installer program to facilitate this.

### Message

> 2. Allow specifying every Nth day of <br>
>    week, i.e., every second Wednesday.
>
>   I did this to calendar by separating the day of week <br>
>   (Wed=4, which one to start on and N with slashes).
>
>   I took modulo the day of year as a starting point so <br>
>   that someone with a desk calendar documenting <br>
>   such things can easily determine the offset (second number).
>
>   I did this while at SGI; alas I don't have a copy of the code.

### Reply

> I can see how this could be useful, <br>
> but I'm not sure how I'd implement it.
>
> Cron currently doesn't keep track of the last time a given <br>
> command was run; whether the current Wednesday is the <br>
> first or second since the command was last run would be <br>
> pretty hard to figure out.
>
> I'd have to keep a database of commands and their execution <br>
> around, and purge it when the crontab was overwritten.
>
> This is too much work for me, but if someone adds it, let me know.