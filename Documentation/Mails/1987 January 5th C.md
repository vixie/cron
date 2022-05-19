<!-- From guy%gorodish@sun Tue Jan  6 20:03:13 1987 -->

<!-- Message-ID: <10944@sun.uucp>
References: <429@vixie.UUCP> <359@bobkat.UUCP>
Sender: news@sun.uucp -->

<!-- Status: RO -->

**Date:** 
<kbd>1987 January 5th</kbd> 
<kbd>Monday</kbd> 
<kbd>12:09:09 GMT</kbd> <br>
**From:** 
<kbd>guy gorodish@sun (Guy Harris)</kbd>  <br>
**Message ID:** 
<kbd>guy gorodish@sun (Guy Harris)</kbd>  <br>

### Message

> Another thing which would be nice is to be <br>
> able to specify which shell to call to give the <br>
> command to.
>
> Well, the obvious choice would be the user's <br>
> shell, but this wouldn't work for accounts like <br>
> "uucico".

### Reply

> I use the owning user's shell, and to handle <br>
> "uucico" I check a list of "acceptable shells" <br>
> (currently compiled in, does anybody mind?), <br>
> substituting a default (compiled in) shell if <br>
> the user's shell isn't on the list.
>
> BTW, "compiled in" means that it's in a .h <br>
> file, easily changed during installation, <br>
> but requiring recompilation to modify.
>
> You don't have to go digging through the code to find it...