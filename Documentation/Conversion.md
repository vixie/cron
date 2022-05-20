
# Conversion

*of **BSD** **Crontab** files.*

BSD: `4.2 - 4.3`

<br>

## Backup

Please make sure you either make a backup of or <br>
keep your original `/usr/lib/crontab` config file.

*While **Cron** now doesn't use it anymore, it might <br>
still come in handy if something goes south.*

<br>
<br>

## Splitting Up

The main goal in the conversion is to edit your <br>
current config into smaller bite sized ones that <br>
fulfill specific roles.

*The biggest feature of this **Cron** is that you can* <br>
*move `news` and `uucp` **Cron** commands into* <br>
*files owned and maintainable by those users.*

<br>
<br>

## Super User

Please remove all the `su` from the **Cron** commands.

*On `4.3`, there's no need for `su` since* <br>
*the user name appears on in command,* <br>
*however I'd still rather have separate* <br>
***Crontabs*** *with separate environments.*

<br>
<br>

## Root

Most commands in most **CronTabs** <br>
🠖 **Are** run by root <br>
⤷ **Have** to be run by root <br>
⤷ **Should** continue be run by root

<br>
<br>

## Structure

***Recommended*** *directory structure for your config files.*

<br>

### Copying

As the `crontab` command copies all used configs into <br>
a protected directory under `<CRONDIR>/SPOOL_DIR`, a <br>
good location doesn't matter but will keep things tidy.

<br>

### Naming

It is **suggested** to use `crontab.src` <br>
as the name for your config files.

<br>

| Type | Suggested Location
|:----:|:------------------
| ***Root*** | `/etc/crontab.src`  **or**  <br>`/usr/adm/crontab.src`
| ***News*** | `/usr/lib/news/crontab.src`
| ***UUCP*** | `/usr/lib/uucp/crontab.src`

<br>
<br>

## Install

Install the configs with the `crontab` command, <br>
probably with `-u <Username>`  🠖  Man Pages.

The `crontab` command can also be used <br>
to examine, replace and delete a **CronTab**.

<br>
<br>

## Examples

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

<br>
<br>

## Mail

You will likely find that after install this version of **Cron** <br>
that your commands are generating a lot of output.

To mitigate this, you can redirect all ***expected*** output <br>
to a per-execution log file, to only keep the last time <br>
the command was run.

This way only ***unexpected*** output will be mailed to you.

*This might take a while to get right, however once it <br>
works, it will be very convenient and worth the effort.*


