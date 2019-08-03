This is the breakdown of how information is extracted from the CAN messages,
if you are unfamilliar with CAN then the following links are useful:

Good get up to speed video:
-https://www.youtube.com/watch?v=FqLDpHsxvf8

A lot of info on how it actually works (not actually necessary to code as this
is all done via library functions and ICs):
-http://www.ti.com/lit/an/sloa101b/sloa101b.pdf

Tutorial used to develop code
-https://www.instructables.com/id/Yes-We-CAN-BUS-With-Arduino-in-30-Seconds/

Documentation on current ECU (Note we use a microsquirt but it has the 
same CAN bus protocol as a megasquirt, also we just use the simplified dash 
broadcasting as the additional information omitted is still received over a 
physical serial connection to a laptop running TunerStudio MS but it is not
needed at all when on track)
-http://www.msextra.com/doc/pdf/Megasquirt_CAN_Broadcast.pdf