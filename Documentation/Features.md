
<br>

[<img height = 2000 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 2000 width = 24% align = right src = '../Resources/Space.svg' >][#]


<div align = center>

# Features

Comparison of ISC to  
BSD 4.2 / 3 & System V

</div>

<br>
<br>

## Environment Variables

These can be set on a per CronTab basis.

<br>

### Syntax

```env
SHELL = /bin/sh
PATH = .:/bin:/usr/bin
Test = 'This is a test'
Hello = "World"
Values = With Spaces
```

<br>

### Variables

*with special meanings.*

#### $\huge\texttt{\textcolor{SkyBlue}{LOGNAME}}$

<pre>
Defaults to data in the users passwd entry.
</pre>

<br>

#### $\huge\texttt{\textcolor{LimeGreen}{MAILTO}}$

<pre>
If set, will mail the output of Cron to  
the user with the specified login name.
<br>
Useful if you decide to use BINMAIL in cron.h  
as it doesn't know anything about aliasing.  
</pre>

#### $\huge\texttt{\textcolor{SkyBlue}{SHELL}}$

<pre>
Defaults to `/bin/sh`.
</pre>

<br>

#### $\huge\texttt{\textcolor{LimeGreen}{USER}}$

<pre>
Read from the users `passwd`
entry and cannot be changed.
</pre>

#### $\huge\texttt{\textcolor{SkyBlue}{HOME}}$

<pre>
Defaults to data in the users `passwd` entry.
</pre>

<br>

#### $\huge\texttt{\textcolor{LimeGreen}{PATH}}$

<pre>

</pre>

#### $\huge\texttt{\textcolor{SkyBlue}{TZ}}$

<pre>
Can be set, but ignored other <br>
than for the command it runs.
</pre>

<br>
<br>

```math
\definecolor{Day-A}{RGB}{169,88,78}
\definecolor{Day-B}{RGB}{156,96,101}
\definecolor{Day-C}{RGB}{141,103,125}
\definecolor{Day-D}{RGB}{129,110,147}
\definecolor{Day-E}{RGB}{113,119,174}
\definecolor{Day-F}{RGB}{102,124,191}
\definecolor{Day-G}{RGB}{83,134,223}
```

## Weekdays

can be specified with their first  `3`  
letters in whatever case you prefer.

<kbd>  $\huge\texttt{\textcolor{Day-A}{Mon}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Day-B}{Tue}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Day-C}{Wen}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Day-D}{Thu}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Day-E}{Fri}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Day-F}{Sat}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Day-F}{Sun}}$  </kbd>

<br>
<br>

[<img height = 2000 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 2000 width = 24% align = right src = '../Resources/Space.svg' >][#]

```math
\definecolor{Month-A}{RGB}{102,191,148}
\definecolor{Month-B}{RGB}{118,190,136}
\definecolor{Month-C}{RGB}{136,190,125}
\definecolor{Month-D}{RGB}{155,189,111}
\definecolor{Month-E}{RGB}{175,189,98}
\definecolor{Month-F}{RGB}{197,188,83}
```

## Months

can be specified with their first  `3`  
letters in whatever case you prefer.

<kbd>  $\huge\texttt{\textcolor{Month-A}{Jan}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-B}{Feb}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-C}{Mar}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-D}{Apr}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-E}{May}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-F}{Jun}}$  </kbd>

<kbd>  $\huge\texttt{\textcolor{Month-A}{Jul}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-B}{Aug}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-C}{Sep}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-D}{Oct}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-E}{Nov}}$  </kbd>  
<kbd>  $\huge\texttt{\textcolor{Month-F}{Dec}}$  </kbd>  

<br>
<br>

## Mixing

Ranges & lists can be mixed.

*Standard Cron doesn't allow `1,3-5`*

<br>
<br>

## Stepping

Ranges can specify a **Step** value.

`10-16/2`  **[≍]**  `10,12,14,16`

<br>
<br>

## Sunday

Can be specified as both `0` & `7`.

*Apparently **BSD** & **ATT** disagree on about this.*

<br>
<br>

## User

Every user gets their own **CronTab** <br>
file like in **System V**s version of **Cron**.

<br>

### BSD 4.2

Only root was allowed to have one.

<br>

### BSD 4.3

- The **CronTab** format was made incompatible.

- Non-root UIDs could run the command.

- Only root could edit the **CronTab** file.

<br>
<br>

## System V

The `crontab` command is loosely compatible with <br>
**System V**, but has been extended with more options.

Running the command without arguments <br>
shows a summary on how to use of the it.

<br>
<br>

## Comments

- Must be on a line by themselves

- Can have leading whitespace

- `#` starts the comment

<br>
<br>

## Auto Reloading

If the `crontab` command changes any **CronTab**, <br>
the `cron` daemon will automatically reload all <br>
tables before the next iteration.

<br>

### Other Crons

- May require you have to kill & restart the daemon.

- May unnecessarily read & parse the config continuously.

<br>
<br>

## Access

The **CronTab** files cannot be read nor <br>
modified other than with `crontab` / `cron`.

*This is to allow for automatic reloading.*

This shouldn't pose a problem however, <br>
as `crontab` allows you to do whatever <br>
you want on your on **CronTab**.

With root you can of course <br>
access anyone's **CronTab**.

<br>
<br>

## MailTo

If any output generated by commands on `stdout` & <br>
`stderr` will be mailed to the owner of the **CronTab**.

Alternatively the `MAILTO` variable is used. <br>
⤷ Check the [Environment Variable](#EnvironmentVariables) section.

### Header

The mail messages header will include:

- The command that was run

- The list of passed environment variables

    *Will at least contain:*

    - `SHELL`
    
    - `HOME`
    
    - `USER`
    
        *`LOGNAME` on **System V**.*
    
<br>
<br>

## DOM / DOW

The situation is odd.  

`* * 1,15 * Sun` will run on:

- 1st

- 15th 

- Sundays

`* * * * Sun` will *only* run on:

- Sundays

`* * 1,15 * *` will *only* run on:

- 1st

- 15th.

This is why we keep `e->dow_star` & `e->dom_star` .

I didn't think up this behavior, it's how **Cron** <br>
has always worked but the documentation <br>
hasn't been very clear.

I have been told that some **AT&T Crons** do not <br>
act this way and do the more reasonable thing, <br>
which is - in my honest opinion - to `or` the <br>
various field - matches together.  

In that sense this **Cron** isn't completely <br>
similar to some of the **AT&T Crons** .


<br>


<!----------------------------------------------------------------------------->

[#]: #


<!----------------------------------------------------------------------------->

[≍]: # 'Is Equivalent To'
