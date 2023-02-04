
[<img height = 1380 width = 21% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1380 width = 21% align = right src = '../Resources/Space.svg' >][#]

<div align = center>

# Installation

</div>

<br>
<br>

1.  Read the notes in the  [`Makefile`]

    <br>

2.  Edit the area marked  `configurable stuff`

    <br>

3.  Adjust the marked area in  [`config.h`]

    <br>
    
4.  Also take a look at  [`pathnames.h`]

    <br>

5.  Ensure you have a  `/var`  directory or  
    a  `/usr/var`  folder that is linked to it.
    
    ```sh
    # Creates the /var directory
    mkdir /var
    ```
    
    ```sh
    # Creates the /usr/var folder & links it
    mkdir /usr/var
    ln -s /usr/var /var
    ```
    
    <br>

6.  Unless you adjust your  [`Makefile`],  you will also need:

    -   `/usr/local/etc`  
    -   `/usr/local/bin`

    *These will have to be created by hand.*

    <br>
    
7.  I keep my **Man Pages** at  `/usr/local/man` , however since  
    you probably won't have the source files, this might not apply.

    Therefore you may have to put the man pages into  `/usr/man/manl` ,  
    which will be hard since this will cause name collisions to occur.

    *Note that the man command was originally written by Bill Joy*  
    *before he left Berkeley, and it contains no AT&T code, so it is in*  
    *UUNET's archive of freely-distributable BSD code.*

    >   **Note**  
    >   `/usr/include/paths.h`  on some **Linux** systems  
    >   shows  `_PATH_SENDMAIL`  to be  `/usr/bin/sendmail`  
    >   even though  `sendmail`  is installed in  `/usr/lib`
    >
    >   *You should check this out.*

    <br>

[<img height = 1800 width = 21% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 1800 width = 21% align = right src = '../Resources/Space.svg' >][#]

8.  Built the binary with:

    ```sh
    make all
    ```
    
    <br>

9.  Install the built program:

    ```sh
    su
    make install
    ```

    *Note that if I can get you to 'su and say' something just*  
    *by asking, you have a very serious security problem on*  
    *your system and you should look into it.*

    Edit your  `/usr/lib/crontab`  file into small pieces.  
    [*» Check the conversion guide.*][Conversion]

    <br>

    ### Examples

    ```sh
    crontab -u uucp -r /usr/lib/uucp/crontab.src
    ```
    
    ```sh
    crontab -u news -r /usr/lib/news/crontab.src
    ```
    
    ```sh
    crontab -u root -r /usr/adm/crontab.src
    ```
    
    <br>

    #### Notes 

    **①**  While installing a config with  `crontab -r`  it's content is copied,  
         this means that any changes to the file won't affect the installed  
         CronTab until re-installing it.
    
    **②**  If no user is specified, the one executing the command will be used.
    
         The  `-u`  option requires root permissions, however on most  
         BSD system being the super user will not automatically make   
         CronTab think of you as root, so still specify the user.

    **③**  The  `-r`  is used to replace specified configurable.
    
    <br>

10. Kill your existing Cron daemon:
    
    ```sh
    ps aux  #  Look for /etc/cron
    ```
    
    <br>
    
11. Find and comment out any lines starting with  
    `/etc/cron`  in  `/etc/rc`  /  `/etc/rc.local`

    Insert a new line starting your Cron daemon,  
    usually  `/usr/local/etc/cron` ➔ [`Makefile`]

    <br>

11. The Cron daemon is started and automatically forked with:
    
    ```sh
    /usr/local/etc/cron  #  Adjust to the path your Cron's path 
    ```
    
    > **Note** 
    >   For those people unfortunate enough to be stuck on a  
    >   AT&T UNIX, you will need the public-domain `libndir`, found  
    >   in the **B News** source and in any `comp.sources.unix` archive.
    >
    >   *You will also need to hack the code some.*

<br>


<!----------------------------------------------------------------------------->

[`pathnames.h`]: ../pathnames.h
[Conversion]: Conversion.md
[`Makefile`]: ../Makefile
[`config.h`]: ../config.h
[#]: #
