
<br>

[<img height = 900 width = 30% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 900 width = 30% align = right src = '../Resources/Space.svg' >][#]

<div align = center>

# Configure

Currently there is no configuration script, as  
such you will have to manually edit a couple  
of files, however a checklist is provided below.


<br>
<br>

## Read

the following sections first.

<br>

[![Button Features]][Features]  
[![Button Install]][Install]  
[![Button Conversion]][Conversion]

</div>

<br>
<br>

## Edit

The following files have to be adjusted by  
the instructions contained within them.

<br>

-   [`config.h`]

	The file contains instructions on what to edit.
	
	Some things are defined in the **Makefile** and  
	do not need to be changed in the config itself.
	
	They will be surrounded by  `#ifndef`  guards.

	<br>

-   [`Makefile`]
	
<br>
<br>

[<img height = 1500 width = 30% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1500 width = 30% align = right src = '../Resources/Space.svg' >][#]

## Execute

Call the following list of commands in order.

<br>

1.  **Build** with the program with:

	```sh
	make
	```
	
	<br>
	
2. **Install** the built binary with:

	```sh
	su
	make install
	```
	
	*The **Man Pages** have to be installed manually.*

	<br>

3.  **Kill** the existing **Cron** process

	<br>

4.  **Create** new **CronTabs** using:

	```
    /usr/lib/{crontab,crontab.local}
    ```
	
	<br>
	
    #### Root
    
    You **can** place all of your settings in the root's CronTab.
    
    <br>
    
    #### User
    
    To keep things tidy and manageable, it is advised to  
    divide your config into purpose based configurations.
    
    You should also remove all  `su`  commands  
    and turn lengthy lists into simple ranges.

	<br>

5.  Start the new **Cron** with root privileges.

	<br>
	
6.  Test and watch the daemon track your changes with:

	```sh
	crontab -r
	```
	
	<br>
	
7.  To keep it your changes, adjust the files found at  
the path listed below to use this version of **Cron**.

    ```
    /etc/{rc,rc.local}
    ```
   

<br>


<!----------------------------------------------------------------------------->

[`config.h`]: ../config.h
[`Makefile`]: ../Makefile
[#]: #

[Conversion]: Conversion.md
[Features]: Features.md
[Install]: Installation.md


<!-------------------------------{ Buttons }----------------------------------->

[Button Conversion]: https://img.shields.io/badge/Conversion-00B0B9?style=for-the-badge&logo=GitExtensions&logoColor=white
[Button Features]: https://img.shields.io/badge/Features-68BC71?style=for-the-badge&logo=AddThis&logoColor=white
[Button Install]: https://img.shields.io/badge/Installation-31A8FF?style=for-the-badge&logo=WindowsTerminal&logoColor=white
