
[<img height = 1900 width = 22% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1900 width = 22% align = right src = '../Resources/Space.svg' >][#]

<div align = center>

# Conversion

*of **BSD** **Crontab** files.*

<kbd> BSD 4.2  </kbd> 
<kbd> BSD 4.3  </kbd>

</div>

<br>

<div align = left>

## 📦  Backup

While **Cron** doesn't use  `/usr/lib/crontab`  config files anymore,  
you should keep it or make a backup in case something goes south.

<br>
<br>

## 🪓  Separation

The main goal of the conversion is split your existing config  
into smaller bite sized pieces that each fulfill a specific role.

*The most significant feature of this Cron is the ability  
to move `news` & `uucp` commands into files owned  
and maintained by those users.*

<br>
<br>

## 🛡  Super User

Please remove all the `su` commands from your config.

*On `BSD 4.3`, there's no need for `su` since the username*  
*appears in the command, however I would recommend*  
*using separate **Crontabs** for separate environments.*

<br>
<br>

## 🥇  Root

Most commands in your most **CronTabs**


**Are** run by **Ｒｏｏｔ**  
**Have** to be run by **Ｒｏｏｔ**  
**Should** continue be run by **Ｒｏｏｔ**

<br>
<br>

## 🏗  Structure

The **recommended** folder layout for your configs.

<br>

### Copying

The  `crontab`  command copies all used configs  
into a protected folder at  `<CRONDIR>/SPOOL_DIR`

This means that it generally doesn't matter where  
you keep your configs, however choosing a good  
location helps to keep things tidy.

<br>

### Naming

It's recommended to name your config files

`crontab.src`

<br>

| Type | Suggested Location
|:----:|:------------------:
| ***Root*** | `/etc/crontab.src`  **or**  <br>`/usr/adm/crontab.src`
| ***News*** | `/usr/lib/news/crontab.src`
| ***UUCP*** | `/usr/lib/uucp/crontab.src`

</div>

<br>
<br>

[<img height = 1750 width = 22% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1750 width = 22% align = right src = '../Resources/Space.svg' >][#]

<div align = left>

## 📥  Installation

Install your configs with the  `crontab`  command, <br>
probably with  `-u <Username>`  ( See man pages )

The  `crontab`  command can also be used  
to examine, replace and delete a **CronTab**.

<br>
<br>

## 🎬  Examples

### 4.2

*On this version your config might look like this:*

```crontab
5 * * * *   su uucp < /usr/lib/uucp/uudemon.hr
10 4 * * *  su uucp < /usr/lib/uucp/uudemon.day
15 5 * * 0  su uucp < /usr/lib/uucp/uudemon.wk
```

*or this:*

```crontab
5 * * * *   echo /usr/lib/uucp/uudemon.hr | su uucp
10 4 * * *  echo /usr/lib/uucp/uudemon.day | su uucp
15 5 * * 0  echo /usr/lib/uucp/uudemon.wk | su uucp
```

<br>

### 4.3

*Here they might look a little bit better already:*

```crontab
5 * * * *   uucp  /usr/lib/uucp/uudemon.hr
10 4 * * *  uucp  /usr/lib/uucp/uudemon.day
15 5 * * 0  uucp  /usr/lib/uucp/uudemon.wk
```

<br>

### Converted

In the updated version you'd want to create a dedicated file, <br>
like `/usr/lib/uucp/crontab.src` to put the `uucp` specific <br>
commands into.

*The converted config might look like this:*

```crontab
# UUCP's Crontab
# at /usr/lib/uucp/crontab.src

SHELL = /bin/sh
PATH = /usr/lib/uucp:/bin:/usr/bin
HOME = /usr/lib/uucp

5 * * * *   uudemon.hr
10 4 * * *  uudemon.day
15 5 * * 0  uudemon.wk
```

<br>

### Alternative

If you run a `4.2` derived **Cron**, you can of <br>
course just install your current **CronTab** in <br>
`toto` as the root's **CronTab**.

It would work exactly the way your current <br>
one does, barring the additional steps in <br>
installing or changing it.

There would still be advantages to this **Cron**, <br>
mostly that you get mail if there is any output <br>
from your **Cron** commands.

</div>

<br>
<br>

[<img height = 400 width = 22% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 400 width = 22% align = right src = '../Resources/Space.svg' >][#]

<div align = left>

## Mail

You will likely find that after install this version of **Cron** <br>
that your commands are generating a lot of output.

To mitigate this, you can redirect all ***expected*** output <br>
to a per-execution log file, to only keep the last time <br>
the command was run.

This way only ***unexpected*** output will be mailed to you.

*This might take a while to get right, however once it <br>
works, it will be very convenient and worth the effort.*

</div>

<br>


<!----------------------------------------------------------------------------->

[#]: #
