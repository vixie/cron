<!-- From qantel!gatech!akgua!blnt1!jat Wed Jan 14 20:00:40 1987 -->

**Date:** 
<kbd>1987 January 13th</kbd> 
<kbd>Tuesday</kbd> 
<kbd>16:39:38 EST</kbd> <br>
**From:** 
<kbd>gatech</kbd> 
<kbd>akgua</kbd> 
<kbd>blnt1</kbd> 
<kbd>jat</kbd> <br>

<!-- Status: RO -->

### Message

> 1) Add some way to tell cron to reread the files, say kill -1 <pid>

### Reply

> whenever the 'crontab' program is run and updates <br>
> a crontab file, a file /usr/spool/cron/POKECRON is <br>
> created; next time the cron daemon wakes up, it <br>
> sees it, and re-reads the crontab files.
>
> I thought of handling the signal; even implemented it.
> 
> Then this clever idea hit me and I ripped <br>
> it all out and added a single IF-statement <br>
> to handle the POKECRON file.

### Message

> 2) Have some kind of retry time so that if a command fails, <br>
> cron will try to execute it again after a certain period.
>
> This is useful if you have some type of cleanup program <br>
> that can run at the scheduled time for some reason <br>
> (such as locked device, unmounted filesystem, etc).

### Reply

> Hmmm, sounds useful.
>
> I could do this by submitting an 'at' job...<br>
> I'll think about it.