
[<img height = 2000 width = 24% align = left  src = '../Resources/Space.svg' >][#]
[<img height = 2000 width = 24% align = right src = '../Resources/Space.svg' >][#]

<div align = center>

# Thanks

`Paul Vixie - 15 January 1990`

<br>

Many people have contributed to Cron,  
many more than I can remember, in fact.

<br>
<br>

</div><div align = right>

**[Rich Salz]** and **[Carl Gutekunst]** were  
each of enormous help to me in V1.

Carl for helping me understand UNIX  
well enough to write it, and Rich for  
helping me get the features right.

<br>
<br>

</div><div align = left>

**[John Gilmore]** wrote me a wonderful review of version 2,  
which took me a whole year to answer, even though it  
made me clean up some really awful things in the code.

*Of course according to John the most awful things are still in there.*

<br>
<br>

</div><div align = right>

**Paul Close** made a suggestion led to the creation  
of  `/etc/crond.pid`  and the mutex locking on it.

<br>
<br>

</div><div align = left>

**Kevin Braunsdorf of Purdue** made a suggestion  
that led to  `@reboot`  and its brothers and sisters.

He also sent in some diffs that lead Cron towards  
compile-ability with **System V**, however without  
at (1) capabilities, this cron isn't going to be that  
useful on System V.

<br>
<br>

</div><div align = right>

**Bob Alverson** fixed a silly bug  
in the line number counting.

<br>
<br>

</div><div align = left>

**[Brian Reid]** suggestions led to the run queue  
& the source-file labeling in installed crontabs.

<br>
<br>

</div><div align = right>

**Scott Narveson** ported version 2 to a Sequent, and sent  
in the single most useful batch of diffs I've ever gotten.

<br>

#### Changes attributable to Scott

<kbd> <br> Sequent-verse support added <br> ( may also help on Pyramids ) <br> </kbd>   
<kbd> <br> Sendmail will not timeout if the <br> cmd is slow to generate output <br> </kbd>
    
<kbd> <br> Misc changes related to the <br> side effects of  `fclose()` <br> </kbd> 
<kbd> <br> Crontab says the correct thing when <br> you do something you shouldn't do <br> </kbd>
    
    
<kbd> <br> Day-of-week names aren't  <br> off by one day anymore <br> </kbd>   
<kbd> <br> The Crontab ( 5 ) man page is longer <br> and it's content is more informative <br> </kbd>

    
<kbd> <br> Null `pw_shell` is dealt with <br> now and defaults to `/bin/sh` <br> </kbd>
    

</div>

<br>


<!----------------------------------------------------------------------------->

[#]: #

[Carl Gutekunst]: https://github.com/alameth
[John Gilmore]: https://en.wikipedia.org/wiki/John_Gilmore_(activist)
[Brian Reid]: https://en.wikipedia.org/wiki/Brian_Reid_(computer_scientist)
[Rich Salz]: https://twitter.com/RichSalz
