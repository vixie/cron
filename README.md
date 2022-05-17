
# Vixie Cron


This is a version of 'cron' that is known to run on most systems.

It is functionally based on the SysV cron, which means that each user can have
their own crontab file (all crontab files are stored in a read-protected
directory, usually /var/cron/tabs).

No direct support is provided for 'at'; you can continue to run 'atrun' from the crontab as you have been doing.

If you don't have atrun (i.e., System V) you are in trouble.

A messages is logged each time a command is executed; also, the files
"allow" and "deny" in /var/cron can be used to control access to the
"crontab" command (which installs crontabs).

It hasn't been tested on SysV, although some effort has gone into making the port an easy one.



