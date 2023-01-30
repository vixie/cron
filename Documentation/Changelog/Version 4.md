
[<img height = 2000 width = 24% align = left  src = '../../Resources/Space.svg' >][#]
[<img height = 2000 width = 24% align = right src = '../../Resources/Space.svg' >][#]

<div align = center>

# Version 4

</div>
    
<br>
<br>
    
<div align = left>

## 4.1

<kbd>  2004 | January  </kbd>

<br>
<br>

## 4.0

<kbd>  2000 | November  </kbd>

<br>
<br>

## 4.0 - B1

<kbd>  1997 | September 7th  </kbd>

<br>
<br>

## Version 3 ⟷ 4

<br>

### 🚨  Security

-   Check `setuid()` result.
    
    *Reported by **Thomas Pollet**.*
    
<br>

### 🧰  Functionality

-   Added `MAIL_FROMUSER` option.

    *See the [`config.h`] comments.*

<br>

### 📦  Miscellaneous 

-   Megapatch from **tcmiller**

    *POXIS compliance & more*

<br>

### 🪳  Bugs

-	Fixed stepsize `0` infinite loop.

-   Handle clock jumps.  

    *From FreeBSD PR `#24485`*

<br>

### 🎁  Features

-   Give Cron a version number and display it.

-   Add `-n` to Cron for `nofork`.

<br>

### 🔬  Evolution

-   `enum` version of **FreeBSD** fixed to `env-var` settings.

-	Merged in many changes from **BSD** and **Linux**.

-	Changes `#12` to `#17` from **tcmiller**.
    
    *For **BSD** alignment.*


<br>

### 💾  Porting
    
-   Fixed syslog configuration bug.

-   Fixups for nextstep.

</div>

<br>


<!----------------------------------------------------------------------------->

[`config.h`]: ../../config.h
[#]: #
