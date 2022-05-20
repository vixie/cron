
# Conversion

*of **BSD** **Crontab** files.*

BSD: `4.2 - 4.3`

<br>

Edit your current crontab `/usr/lib/crontab` <br>
into little pieces, with each users' commands <br>
in a different file.

This is different on `4.2` and `4.3`, but I'll get to that below.

The biggest feature of this cron is that you can <br>
move `news` and `uucp` cron commands into files <br>
owned and maintainable by those two users.

You also get to rip all the fancy `su` <br>
footwork out of the `cron` commands.

On `4.3`, there's no need for the `su` stuff since <br>
the user name appears on each command -- <br>
but I'd still rather have separate crontabs with <br>
separate environments and so on.

Leave the original `/usr/lib/crontab`!

This cron doesn't use it, so you may as well keep <br>
it around for a while in case something goes <br>
wakko with this fancy version.

Most commands in most crontabs are run by root, <br>
have to run by root, and should continue to be run by root.

They still have to be in their own file; I recommend <br>
`/etc/crontab.src` or `/usr/adm/crontab.src`.

`uucp`s commands need their own file; <br>
how about `/usr/lib/uucp/crontab.src`?

`news` also, perhaps in `/usr/lib/news/crontab.src`...

I say `how about' and `perhaps' because it really <br>
doesn't matter to anyone (except you) where you <br>
put the crontab source files.

The `crontab` command COPIES them into a protected <br>
directory `CRONDIR/SPOOL_DIR` in `cron.h`, named after <br>
the user whose crontab it is.

If you want to examine, replace, or delete a crontab, <br>
the `crontab` command does all of those things.

The various `crontab.src` (my suggested name for them) <br>
files are just source files --- they have to be copied to <br>
SPOOLDIR using `crontab` before they'll be
executed.

On `4.2`, your crontab might have a few lines like this:

```src
5 * * * *   su uucp < /usr/lib/uucp/uudemon.hr
10 4 * * *  su uucp < /usr/lib/uucp/uudemon.day
15 5 * * 0  su uucp < /usr/lib/uucp/uudemon.wk
```

...or like this:

```src
5 * * * *   echo /usr/lib/uucp/uudemon.hr | su uucp
10 4 * * *  echo /usr/lib/uucp/uudemon.day | su uucp
15 5 * * 0  echo /usr/lib/uucp/uudemon.wk | su uucp
```

On 4.3, they'd look a little bit better, but not much:

```src
5 * * * *   uucp  /usr/lib/uucp/uudemon.hr
10 4 * * *  uucp  /usr/lib/uucp/uudemon.day
15 5 * * 0  uucp  /usr/lib/uucp/uudemon.wk
```

For this cron, you'd create `/usr/lib/uucp/crontab.src` <br>
(or wherever you want to keep uucp's commands) which <br>
would look like this:

```src
# /usr/lib/uucp/crontab.src - uucp's crontab
#
PATH=/usr/lib/uucp:/bin:/usr/bin
SHELL=/bin/sh
HOME=/usr/lib/uucp
#
5 * * * *   uudemon.hr
10 4 * * *  uudemon.day
15 5 * * 0  uudemon.wk
```

The application to the `news` cron commands <br>
(if any) is left for you to figure out.

Likewise if there are any other cruddy-looking `su` <br>
commands in your crontab commands, you don't <br>
need them anymore:

just find a good place to put the `crontab.src` <br>
(or whatever you want to call it) file for that user, <br>
put the cron commands into it, and install it using <br>
the `crontab` command (probably with `-u USERNAME`, <br>
but see the man page).

If you run a 4.2-derived cron, you could of course just <br>
install your current crontab in toto as root's crontab.

It would work exactly the way your current one does, <br>
barring the extra steps in installing or changing it.

There would still be advantages to this cron, mostly that you <br>
get mail if there is any output from your cron commands.

One note about getting mail from cron: 

you will probably find, after you install this version <br>
of cron, that your cron commands are generating <br>
a lot of irritating output.

The work-around for this is to redirect all EXPECTED <br>
output to a per-execution log file, which you can <br>
examine if you want to see the output from the <br>
"last time" a command was executed; if you get <br>
any UNEXPECTED output, it will be mailed to you.

This takes a while to get right, but it's amazingly convenient.

Trust me.

