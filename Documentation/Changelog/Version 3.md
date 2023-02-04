
[<img height = 1940 width = 24% align = left  src = '../../Resources/Space.svg' >][#]
[<img height = 1940 width = 24% align = right src = '../../Resources/Space.svg' >][#]

<div align = center>

# Version 3

</div>

<br>
<br>

<div align = left>

## Patch 2

<kbd>  1994 | December 12th  </kbd>

-   `gethostname()`  is now available in  `compat.c`

-   Fixed various  `flock()`  problems.

-   Fixed environment importing.

-   `Coherent`  is now supported.

<br>
<br>

## 3.1

<kbd>  1993 | Some time after ..  </kbd>

<br>
<br>

## 3.0 

<kbd>  1993 | December 27th  </kbd>

<br>
<br>

## Version 2 ⟷ 3

<kbd>  1993 | December 29th  </kbd>

<br>

-   The  `crontab`  command now conforms to `POSIX 1003.2`

    This means that when you install this Cron and you  
    have any  `crontab`  command lines floating around  
    in shell scripts such as  `/etc/rc`  or  `/etc/rc.local`  
    you will need to change them.
    
    <br>

-   I have integrated several changes made by **BSDi** for their  
    `BSD / 386`  operating system, these were offered to me   
    before I started consulting for them, so it is safe to say  
    that they were intended for publication.

    <br>

    For compatibility with  `BSD 4.3`  the name of  
    the daemon was changed:  `crond`  🠖  `cron`

    <br>

    For the same reason, support for reading  
    the  `/etc/crontab`  file has been added. 

    It differs from other configs, in that every  
    entry has an extra field for a username.
    
    ```
    <Time> <Username> <Command>
    ```
    
    It also isn't installed with the CronTab command,  
    instead it is automatically read on startup, as well  
    as every time the file is modified.
    
    <br>

-   Added  `-e`  option to  `crontab`

    *Nine people also sent me diffs to add this option,*  
    *but I had already implemented it on my own.*

    I actually released an interim version for limited testing,  
    I think it was version  `2.2` , and got a chance to fix a  
    bad security bug in the  `-e`  option thanks to **XXX**.
    
    <br>
    
[<img height = 1850 width = 24% align = left  src = '../../Resources/Space.svg' >][#]
[<img height = 1850 width = 24% align = right src = '../../Resources/Space.svg' >][#]

-   The daemon used to be extraordinarily sloppy in its use of  
    file descriptors, as it left a lot of them open in spawned jobs.

    This caused a lot of problems, including one with `sh` /  `csh`  
    that when called in commands thought they were sub-shells.

    This happened since traditionally they used hidden  
    file descriptors to communicate with sub-shells.
    
    Chances are good that any such issues with  
    `sh`  /  `csh`  scripts should be fixed in V3.

    <br>

-   About a dozen people have reminded me that I  
    forgot to initialize  `crontab_fd`  in  [`database.c`]

    **Keith Cantrell** was the first, so he gets the point.
    
    <br>

-   **Steve Simmons** reminded me that once an account has been  
    deleted from the system,  `crontab -u USER -d`  will not work.

    My solution is to suggest to all of you that before you delete a  
    user's account, you first delete their crontab file if there is one.

    For Cron, usernames can never be treated as arbitrary strings,  
    either they are valid or they are not, I won't make an exception  
    for the  `-d`  case considering the security implications.

    It is trivial for root users to delete entries by hand anyways.

    <br>

-   **Dan O'Neil** as well as others reminded me that I forgot to reset  
    `log_fd`  in  [`misc.c`] , however the real bug is that it should have  
    been open in the parent.

    <br>

-   **Hans Trompert** informed me about and **Peter Kabal** sent me  
    the patch for missing  `#ifdef DEBUGGING`  guards in  [`misc.c`]
    
    <br>

-   **Steve Simmons** & **Russell Nelson** told me about  
    the missing  `#include <syslog.h>`  in [`misc.c`]
    
    This explains why a lot of other people complained that it  
    wasn't using syslog even when they configured it that way.
    
    <br>

-   **Dave Burgess** pointed out the bogus code of an interim version  
    of the daemon that tried to  `stat`  every file before executing it.
    
    This turned out to be a horribly bad idea since finding the name  
    of a file from a shell command is a hard job, that's why we have  
    shells, right?
    
    <br>

-   **Dennis R. Conley** sent in a suggestion for **MMDF**  
    systems that I've added as a comment in [`cron.h`]
    
    <br>

-   **Mike Heisler** noted that I used comments in the CONVERSION  
    file which are documented to be illegal in the man pages.
    
    <br>

-   **Irving Wolfe** sent me some very cheerful changes for a **NeXT**  
    system, but I consider the system itself broken and can't bring  
    myself to  `#ifdef`  for something as screwed up as that system.

    However, various other people sent me smaller patches that  
    appear to have made Cron build and run correctly on the  
    latest **NeXT** machines, with or without the  `-posix`  CFLAG.

    **Irving** also asked for a per-job  `MAILTO` which was finally  
    added later when I integrated the  `BSD / 386`  changes  
    contributed by **BSDi**, and generalized some of the parsing.
    
    <br>

[<img height = 1600 width = 24% align = left  src = '../../Resources/Space.svg' >][#]
[<img height = 1600 width = 24% align = right src = '../../Resources/Space.svg' >][#]
        
-   Lots of folks complained that the auto-generated  `Date:`  
    header wasn't in **ARPA** format, which I didn't understand.

    Either folks will use **Sendmail** and not generate a  `Date:`  
    at all, since Sendmail will do it, or folks will use something  
    other than Sendmail that won't care about  `Date:`  formats.

    But I've 'fixed' it anyway ...
    
    <br>

-   Several people suggested that  `*`  should be able to take a  
    `/step`, one person even suggested that  `N/step`  ought to   
    mean  `N-last/step` , but that's stretching things a bit far.

    `*/step`  seems quite intuitive to me, so I've added it.

    **Colin Plumb** sent in the first and most polite request.

    <br>

-   As with every release of **Cron**,  `BIND`  and seemingly  
    everything else I do has one user stand out with the   
    most critical but also the most useful analysis on it.
    
    <br>

-   **Cron** V3's high score belongs to **Peter Holzer**, who sent in  
    the nicest looking patch for the  `%`  interpretation problem  
    and also help me understand a tricky bit of badness in the  
    `log_fd`  problem.
    
    <br>

-   `agulbra@flode.nvg.unit.no`  wins the honor of being the  
    first person to point out the security hole in  `crontab -r`
    
    <br>

-   Several folks pointed out that  `log_it()`  
    needs to exist even if logging is disabled.

    Some day I will create a tool that will compile a subsystem <br>
    with every possible combination and permutation of `#ifdef` <br>
    options, but meanwhile thanks to everybody.
    
    <br>

-   `job_runqueue()`  was using storage after freeing it, since  
    **Jordan** told me back in 1983 that C let you do that, and I  
    believed him in 1986 when I wrote all this junk.

    Linux was the first to die from this error and the Linux users  
    sent me the most amazing, um, collection of patches for this.

    Thanks for all the fish.
    
    <br>

-   **Jeremy Bettis** reminded me that  `popen()`  isn't safe.

    <br>

-   I grabbed **Ken Arnold's** version of  `popen`  and  
    `pclose` from the FTPD and hacked it to taste.

    We're safe now, from this at least.
    
    <br>

-   **Branko Lankester** sent me a very timely and helpful fix  
    for a looming security problem in my  `crontab -e`  code.

</div>

<br>


<!----------------------------------------------------------------------------->

[`database.c`]: ../../database.c
[`cron.h`]: ../../cron.h
[`misc.c`]: ../../misc.c

[#]: #
