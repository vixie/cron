
<!-- From drw@mit-eddie Wed Dec 31 18:25:27 1986 -->

**Date:** 
<kbd>1986 December 31</kbd> 
<kbd>Wednesday</kbd> 
<kbd>14:28:19 EST</kbd> <br>
**From:** 
<kbd>drw@mit-eddie (Dale Worley)</kbd>  <br>
**To:** 
<kbd>mit-eddie</kbd> 
<kbd>vixie</kbd> 
<kbd>paul</kbd> <br>

<!-- **Status:** `RO` -->

### Message

> We have a lot of lines in our crontab of the form
>
> ```src
> 00 12 * * * su user < /usr/users/user/script.file
> ```
>
> This barfs (silently!) on our system (Dec Ultrix 1.2 == 4.2bsd) if user's shell is csh.
>
> This, I am told, is because csh requires that <br>
> the environment be set up in certain ways, <br>
> which cron doesn't do.
>
> *Actually, I believe, it is because `/etc/rc`, which runs cron, <br>
> doesn't set up the environment enough for csh to run, and <br>
> cron just inherits the situation.*
>
> Anyway, the point is that if you find out what csh really <br>
> needs in its environment, you might want to set up cron <br>
> to provide some reasonable defaults 
>
> *if it isn't supplied by cron's parent.*
>
> Also, could you tell me what csh needs, if <br>
> you find out, so we can hack our `/etc/rc`?

### Reply

> well, the environment IS a problem.
>
> processes that cron forks will inherit the environment <br>
> of the person who ran the cron daemon... 
>
> I plan to edit out such useless things as TERMCAP, <br>
> TERM, and the like; supply correct values for HOME, <br>
> USER, CWD, and whatever else comes to mind.
>    
> I'll make sure csh works...