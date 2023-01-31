
[<img height = 1600 width = 24% align = left  src = '../../Resources/Space.svg' >][#]
[<img height = 1600 width = 24% align = right src = '../../Resources/Space.svg' >][#]

<div align = center>

# Version 2

</div>

<br>
<br>

<div align = left>

## 2.2

<kbd>  1992  </kbd>

<br>
<br>

## 2.1

<kbd>  1991 | May 29th  </kbd>

<br>
<br>

## 2.0

<kbd>  1990 | July 5th  </kbd>

<br>
<br>

## 2.0 - Beta

<kbd>  1988 | December 9th  </kbd>

<br>
<br>

## Version 1 ⟷ 2

<kbd>  1988 | February 8th  </kbd>

<br>

Many changes were made in a rash of activity  
about six months ago, the exact list of which  
is no longer that clear in my memory.

I know that version 1 used a file called  `POKECRON` ,  
in the  `/usr/spool/cron`  directory, to tell if it was  
time to re-read all CronTab configs.

Version 2 uses the modification time of config  
files in the CronTab directory, where it re-reads  
those files whose modification time has changed.

Note that the crontab (1) command will do a  `utimes`  call to  
check if the modification time of the directory has changed.

This is done since the filename / inode will often remain  
the same after a replacement and the modification time  
wouldn't change in that case.

<br>

### <kbd>  1988 | February 8th  </kbd>

<br>

**Toerless Eckert** gave me the idea to increase the  
environment variable string limit to fix problems  
some people had with their  `PATH`  files.

`100`  🠖  `1000`

</div>

<br>

[<img height = 1400 width = 24% align = left  src = '../../Resources/Space.svg' >][#]
[<img height = 1400 width = 24% align = right src = '../../Resources/Space.svg' >][#]

<div align = left>

### <kbd>  1988 | February 16th  </kbd>

<br>

-   Moved  `/usr/spool/cron/crontabs`  
    to  `/usr/lib/cron/tabs`

    <br>

-   Added  `allow`  /  `deny`

	⤷  `/usr/lib/cron/{allow,deny}`
	
	⤷  Since the **System V** naming for this depends on  `at`  
         using the same directory, which would be stupid.
	
    <br>
    
	*Hint, use  `/usr/{lib,spool}/at`*

<br>

### <kbd>  1988 | February 22nd  </kbd>

<br>

Use  `getpwent()`  to read  `passwds`  
and try to open each CronTab config.

                      🠗

Read the `spool` directory for crontabs <br>
& look each one up using `getpwnam()`

<br>

### <kbd>  1988 | December 9th  </kbd>

<br>

-   Now syncs to  `00`  after every minute

	⤷ Makes **Cron** predictable.
	
    <br>
    
-   Added logging to  `/var/cron/log`

<br>

### <kbd>  1990 | April 14th  </kbd>

<br>

*Changes since December 1989*

-   Fixed a number of bugs reported by **John Gilmore**.

-   Added  `syslog`  as per **Keith Bostic**.

-   Added security features:

	Commands can only be run by, the owner <br>
	of / with write permission to, the crontab.

	*Not working well yet*


</div>

<br>


<!----------------------------------------------------------------------------->

[#]: #
