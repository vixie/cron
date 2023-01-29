
# Install

1. Read the comments at the top of the Makefile.

2. Edit the area marked `configurable stuff`.

3. Edit config.h

    The stuff I expect you to change is down a bit from the top of the file, but it's clearly marked.
    
4. Also look at pathnames.h

5. You don't have to create the `/var/cron` or `/var/cron/tabs` directories, since both the daemon and the `crontab` program will do this the first time they
run if they don't exist.

    You do need to have a `/var`, though -- just `mkdir /var` if you don't have one, or you can `mkdir /usr/var` `ln -s /usr/var /var` if you expect your `/var` to have a lot of stuff in it.

6. You will also need `/usr/local/etc` and `/usr/local/bin` directories unless you change the **Makefile**.

These will have to be created by hand, but if you are a long-time Usenet user you probably have them already.

`/usr/local/man` is where I keep my man pages, but I have the source for `man` and you probably do not.

Therefore you may have to put the man pages into `/usr/man/manl`, which will be hard since there will be name collisions.

(Note that the man command was originally written by Bill Joy before he left Berkeley, and it contains no AT&T code, so it is in UUNET's archive of freely-distributable BSD code.)

LINUX note: `/usr/include/paths.h` on some **Linux** systems shows `_PATH_SENDMAIL` to be `/usr/bin/sendmail` even though `sendmail` is installed in `/usr/lib`.	you should check this out.

```sh
make all
```

```sh
su
make install
```

Note that if I can get you to "su and say" something just by asking, you have
a very serious security problem on your system and you should look into it.

Edit your `/usr/lib/crontab` file into little pieces -- see the **CONVERSION** file for help on this.

Use the `crontab` command to install all the little pieces you just created.

Some examples (see below before trying any of these!)


```sh
crontab -u uucp -r /usr/lib/uucp/crontab.src
crontab -u news -r /usr/lib/news/crontab.src
crontab -u root -r /usr/adm/crontab.src
```

Notes on above examples: 

(1) the .src files are copied at the time the command is issued; changing the source files later will have no effect until they are reinstalled with another `crontab -r` command.  

(2) The crontab command will affect the crontab of the person using the command unless `-u USER` is given; `-u` only works for root.

When using most `su` commands under most BSD's, `crontab` will still think of you as yourself even though you may think of yourself as root -- so use `-u` liberally.

(3) the `-r` option stands for `replace`; check the man page for crontab(1) for other possibilities.


Kill your existing cron daemon -- do `ps aux` and look for `/etc/cron`.


Edit your `/etc/rc` or `/etc/rc.local`, looking for the line that starts up
`/etc/cron`.

Comment it out and add a line to start the new cron daemon -- usually `/usr/local/etc/cron`, unless you changed it in the **Makefile**.

Start up this cron daemon yourself as root.  Just type `/usr/local/etc/cron`
(or whatever); no '&' is needed since the daemon forks itself and the
process you executed returns immediately.

ATT notes: for those people unfortunate enough to be stuck on a AT&T UNIX,
you will need the public-domain "libndir", found in the B News source and in
any comp.sources.unix archive.  You will also need to hack the code some.