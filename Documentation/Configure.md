
# Configure

As there isn't a `Configure` script, you unfortunately <br>
will have to manually edit a couple of files, however <br>
in the following you will find a checklist.

<br>

## Read

*The following files:*

- **[FEATURES]**
- **[INSTALL]**
- **[CONVERSION]**

<br>

## Edit

*The following code:*

- [`config.h`][Config]

	*The file contains instructions on what to edit.*
	
	*Some things are defined in the **Makefile** and* <br>
	*do not need to be changed in the config itself.*
	
	*They will be surrounded by `#ifndef` & `#endif`.*

	<br>

- [`Makefile`][Makefile]

	*This file also contains instructions.*
	
<br>

## Execute

*The following commands:*

1. Build with:

	```sh
	make
	```
	
	<br>
	
2. Install with:

	```sh
	su
	make install
	```
	
	*The **Man Pages** have to be installed manually.*

	<br>

3. Kill the existing **Cron** process

	<br>

4. Create new **CronTabs** using:

	`/usr/lib/{crontab,crontab.local}`
	
	<br>
	
	*Either put all of them in the roots **Crontab** or:* <br>
	
	- Divide it up 
	
	- Remove all the `su` commands
	
	- Collapse the lengthy lists into ranges with steps 
	
	<br>
	
	Basically, this step is as much work as you want to make it.

	<br>

5. Start the new **Cron**

	*Requires root*
	
	<br>
	
6. Test it with:

	```sh
	crontab -r
	```
	
	*And watch the daemon track your changes.*
	
	<br>
	
7. To keep it, adjust `/etc/{rc,rc.local}` <br>
   to use the new version of **Cron**
   
<br>
		
		
<!----------------------------------------------------------------------------->

[CONVERSION]: ../CONVERSION
[FEATURES]: ../FEATURES
[Makefile]: ../Makefile
[INSTALL]: ../INSTALL
[Config]: ../config.h
