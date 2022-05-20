<!-- From ptsfa!ames!seismo!cbmvax!devon!paul Tue Jan  6 05:50:17 1987 -->

**Date:** 
<kbd>1987 January 5th</kbd> 
<kbd>Monday</kbd> 
<kbd>09:29:57</kbd> <br>
**From:** 
<kbd>ames</kbd> 
<kbd>seismo</kbd> 
<kbd>cbmvax</kbd> 
<kbd>devon</kbd> 
<kbd>paul</kbd>  <br>
**To:** 
<kbd>cbmvax</kbd> 
<kbd>seismo</kbd> 
<kbd>nike</kbd> 
<kbd>ptsfa</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>


<!-- Status: RO -->

### Message

> One problem that has always plagued <br>
> me with cron is the assumed ORing.
>
> I'd like to see some type of ANDing implemented.
>
> I guess I can best describe this by example. <br>
> Say I have the following line in my crontab
>
> file:
>
> ```crontab
> *  *  4-31  *  1-6	/usr/bin/command
> ```
>
> What this does is run 'command' on the 4th thru 31st <br>
> days of the month, AND on Monday thru Saturday; <br>
> which probably means running it every day of the <br>
> month (unless Sunday falls on days 1-3).
>
> This happens because cron runs the command <br>
> if the day-of-month OR the day-of-week is true.
>
> What I'd like to happen with the above line is to run <br>
> the command ONLY on Monday thru Saturday any <br>
> time after the 3rd of the month, e.g. if the <br>
> day-of-month AND the day-of-week are true.
>
> My proposal to you is to implement some <br>
> special chars for the first five fields.
>
> Examples:
>
> ```crontab
> *  *  !1-3  *  1-6	/usr/bin/command
> ```
>
> (run command Mon-Sat, but NOT [!] on the first 3 days of the month)
>
> ```crontab
> *  *  &4-31 *  &1-6	/usr/bin/command
> ```
> 
> (run command if day-of-month AND day-of-week are true)
> 
> Get the picture?
> 
> This would be compatable with existing versions <br>
> of cron (which wouldn't currently be using any <br>
> special characters, so that old crontabs would <br>
> be handled correctly).

### Reply

> This message made me aware of the actual <br>
> boolean expression involved in a crontab entry.
>
> I'd assumed that it was
>
> (minute && hour && DoM && month && DoW)
>
> But it's really
>
> (minute && hour && month && (DoM || DoW))
>
> I can see some value in changing this, but with a <br>
> fixed order of fields, operators get to be kindof <br>
> unary, which && and || really aren't.    
> 
> If someone has an idea on a syntax that allows <br>
> useful variations to the standard (&& && && (||)) <br>
> default, please suggest.