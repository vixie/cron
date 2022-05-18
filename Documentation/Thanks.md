
# Thanks


`15 January 1990` <br>
**Paul Vixie**

Many people have contributed to cron. <br>
Many more than I can remember, in fact.

**[Rich Salz]** and **[Carl Gutekunst]** were <br>
each of enormous help to me in V1.

Carl for helping me understand UNIX <br>
well enough to write it, and Rich for <br>
helping me get the features right.

<br>

**[John Gilmore]** wrote me a wonderful review of V2, which <br>
took me a whole year to answer even though it made me <br>
clean up some really awful things in the code.

*According to John the most awful things are still in here, of course.*

<br>

**Paul Close** made a suggestion which led to <br>
`/etc/crond.pid` and the mutex locking on it.

<br>

**Kevin Braunsdorf of Purdue** made a suggestion that led <br>
to `@reboot` and its brothers and sisters; he also sent some <br>
diffs that lead cron toward compile-ability with **System V**, <br>
though without at (1) capabilities, this cron isn't going to <br>
be that useful on System V.

<br>

**Bob Alverson** fixed a silly bug in the line number counting.

<br>

**[Brian Reid]** made suggestions which led to the run <br>
queue and the source-file labeling in installed crontabs.

<br>

**Scott Narveson** ported V2 to a Sequent, and sent in the <br>
most useful single batch of diffs I got from anybody.

Changes attributable to Scott are: <br>
   🠖 Sendmail won't time out if the command is slow to generate output <br>
   🠖 Day-of-week names aren't off by one anymore <br>
   🠖 Crontab says the right thing if you do something you shouldn't do <br>
   🠖 Crontab(5) man page is longer and more informative <br>
   🠖 Misc changes related to the side effects of fclose() <br>
   🠖 Sequent "universe" support added (may also help on Pyramids) <br>
   🠖 Null pw_shell is dealt with now; default is /bin/sh


<!----------------------------------------------------------------------------->

[Carl Gutekunst]: https://github.com/alameth
[John Gilmore]: https://en.wikipedia.org/wiki/John_Gilmore_(activist)
[Brian Reid]: https://en.wikipedia.org/wiki/Brian_Reid_(computer_scientist)
[Rich Salz]: https://twitter.com/RichSalz
