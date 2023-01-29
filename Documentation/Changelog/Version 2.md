## Version 2

### 2.2

<kbd>Some time in 1992</kbd>

### 2.1

<kbd>May 29, 1991</kbd>

### 2.0

<kbd>July 5, 1990</kbd>

### 2.0-beta

<kbd>December 9, 1988</kbd>

### V2 vs V1

<kbd>1988 February 8th</kbd>

Many changes were made in a rash of activity <br>
about six months ago, the exact list of which <br>
is no longer clear in my memory.

I know that V1 used a file called `POKECRON` in <br>
`/usr/spool/cron` to tell it that it was time to <br>
re-read all the crontab files.

V2 uses the `modtime` the `crontab` directory <br>
as a flag to check out the crontab files; those <br>
whose modtime has changed will be re-read, <br>
and the others left alone.

Note that the crontab(1) command will do a <br>
`utimes` call to make sure the `mtime` of the <br>
dir changes, since the filename / inode will <br>
often remain the same after a replacement <br>
and the mtime wouldn't change in that case.

<br>

#### <kbd>1988 February 8th</kbd>

- Environment variables strings can be longer:

	`100`  🠖  `1000`
	
	*This was needed for `PATH`* <br>
	*variables on some systems.*
	
	Thanks to **Toerless Eckert** for this idea.

<!-- E-mail: UUCP: ...pyramid!fauern!faui10!eckert -->

<br>

#### <kbd>1988 February 16th</kbd>

- Moved `/usr/spool/cron/crontabs` to `/usr/lib/cron/tabs`

- Added `allow` / `deny`

	⤷ `/usr/lib/cron/{allow,deny}`
	
	⤷ Since the **System V** naming for this depends on <br>
	`at` using the same directory, which would be stupid.
	
	*Hint: Use `/usr/{lib,spool}/at`*

<br>

#### <kbd>1988 February 22nd</kbd>

Use `getpwent()` to read `passwds` <br>and try to open each crontab.

                      🠗

Read the `spool` directory for crontabs <br>
& look each one up using `getpwnam()`.

<br>

#### <kbd>1988 December 9th</kbd>

- Now syncs to `00` after every minute

	⤷ Makes **Cron** predictable.
	
- Added logging to `/var/cron/log`.

<br>

#### <kbd>1990 April 14th</kbd>

*Actually, changes since December 1989*

- Fixed a number of bugs reported by **John Gilmore**.

- Added `syslog` per **Keith Bostic**.

- Added security features:

	Commands can only be run by, the owner <br>
	of / with write permission to, the crontab.

	*Not working well yet*


<br>
<br>
