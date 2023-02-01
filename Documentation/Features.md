
<br>

[<img height = 1900 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1900 width = 24% align = right src = '../Resources/Space.svg' >][#]


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

<br>

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

<br>

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

<br>

#### $\huge\texttt{\textcolor{SkyBlue}{HOME}}$

<pre>
Defaults to data in the users `passwd` entry.
</pre>

<br>

#### $\huge\texttt{\textcolor{LimeGreen}{PATH}}$

<pre>

</pre>

<br>

#### $\huge\texttt{\textcolor{SkyBlue}{TZ}}$

<pre>
Can be set, but ignored other <br>
than for the command it runs.
</pre>

<br>
<br>

[<img height = 1950 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1950 width = 24% align = right src = '../Resources/Space.svg' >][#]

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

Unlike standard Cron, ranges & lists can be mixed.

```
1,3-5
```

<br>
<br>

## Stepping

Ranges can specify a value to step width.

```
10-16/2  ≍  10,12,14,16
10-16/3  ≍  10,13,16
```

<br>
<br>

## Sunday

The day can be specified with both  `0`  and  `7`  
which **BSD** and **ATT** apparently disagree about.

<br>
<br>

## User

Every user has their own CronTab config,  
as it is also done in **System V**'s Cron flavor.

<br>

### BSD 4.2

In this version of BSD, only the root  
user could have a CronTab config.

<br>

### BSD 4.3

- The **CronTab** format was made incompatible.

- Non-root UIDs could run the command.

- Only root could edit the **CronTab** file.

<br>
<br>

## System V

The  `crontab`  command is loosely compatible with  
**System V**, but has been extended with more options.

Running the command without arguments  
shows a summary on how to use of the it.

[<img height = 1500 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1500 width = 24% align = right src = '../Resources/Space.svg' >][#]

<br>
<br>

## Comments

- Must be on a line by themselves

- Can have leading whitespace

- `#`  starts the comment

<br>
<br>

## Auto Reloading

If the  `crontab`  command makes any changes,  
the Cron daemon will reload all tables before the  
next iteration automatically.

<br>

### Other Crons

-   May require you have to kill and restart the daemon.

-   May unnecessarily read & parse the config continuously.

<br>
<br>

## Access

The **CronTab** files cannot be read nor modified other  
than with the  `crontab`  /  `cron`  commands, this is  
to allow for automatic reloading.

This shouldn't pose a problem however, as  `crontab`  
allows you to adjust everything in your own **CronTab**.

With root you can of course access anyone's **CronTab**.

<br>
<br>

## MailTo

Any output generated by commands to  `stdout`  and  
`stderr`  will be mailed to the owner of the **CronTab**.

Alternatively the  `MAILTO`  variable is used.  
⤷ Check the **[Environment Variable]** section.

<br>

### Header

The email messages header will include:

-   The command that was run by Cron

-   The list of passed environment variables of  
    which the following will always be present:

    `SHELL`    `HOME`    `USER`    `LOGNAME`

    *LogName is only passed on System V*
    
<br>
<br>

[<img height = 1000 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1000 width = 24% align = right src = '../Resources/Space.svg' >][#]

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

[Environment Variable]: EnvironmentVariables
[#]: #
