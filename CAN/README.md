# Read CAN function: (INSERT NAME HERE)

Previous code worked perfectly fine but was very rigid and non adaptable.
All ECUs have a tabulated form similar to 
[this PDF](http://www.msextra.com/doc/pdf/Megasquirt_CAN_Broadcast.pdf).
As we are going to be working with different ECUs in the future and
potentially this year, we want the code structured in a way so that we can
easily modify a form of "table" in the code to change ECU.

Note this will require access to an ECU to test so if you are in Cambridge
I can sort out access for you but otherwise I am in Cambridge for summer
so I can test it for you.

See the README in the old code for documentation to get you going

## Function Requirements:
    
1. Solution not necessarily in a function form but rather write a body 
of code in which we will implement the other functions within
  
2. Rather than hard code each data field in if statements (what I did)
have the code loop through a form of table.
[This](https://github.com/hugohadfield/PycroSquirt?fbclid=IwAR2VfK3nLpm_gJR32rTgj_sBaHsmAMyxUEX0m65-PVn7jPGLHAkJ7-6FZCU)
is an alumni's code which looped through a table on a text
file when we were based on rasberry pi. Essetially what this is doing.
  
3. Easy way to access each variable extracted to use in other functions

