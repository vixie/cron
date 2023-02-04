
<!-- From bobkat!pedz Tue Jan  6 20:02:10 1987 -->

**Date:** 
<kbd>1987 January 2nd</kbd> 
<kbd>Friday</kbd> 
<kbd>17:34:44 GMT</kbd> <br>
**From:** 
<kbd>pedz@bobkat.UUCP (Pedz Thing)</kbd>  <br>

<!-- Status: RO -->

### Message

> Log files!
>
> It would be nice to be able to specify a log for cron <br>
> itself and also a log for each program's stdout and <br>
> stderr to go to.
>
> The latter can of course be done with > and 2> but <br>
> it would be nice if there could be a single line with <br>
> some sort of pattern like `> /usr/spool/log/%' and <br>
> the command would be substituted for the %.
>
> Another thing which would be nice is to be able to <br>
> specify which shell to call to give the command to.

### Reply

> Log files are done with mail.
>
> The '%' idea could be useful if a different character <br>
> were used (% is special to cron, see man page);
>
> a different directory would have to be chosen, since <br>
> each user has their own crontab file; and something <br>
> intelligent would have to be done in the file naming, <br>
> since the first word of the command might be <br>
> ambiguous (with other commands).
>
> In short, it's too much work. <br>
> Sorry.