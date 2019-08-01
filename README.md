# FBR20-Electronics

This repo houses all the code the car needs to run, separated into steering 
wheel and datalogger files.

////////////////////////////////////////////////////////////////////////////////

Each function to be made is described down below, if someone is already working
on one and you want to join, contact them and see if you can help before writing
your own code. Otherwise just write your name down and contact me (will) for
any questions/purchasing.

////////////////////////////////////////////////////////////////////////////////

Steering Wheel LEDs: (INSERT NAME HERE)

    On the steering wheel we have rpm LEDs and indicator LEDs, previously
    they were fixed colour LEDs and each one had its own pin on the arduino to 
    drive it. This year we want to switch to using WS2812B LEDs (you can find a 
    better/ alternative solutions, these are just common) They are RGB LEDs that
    are controlled by clocking information through them in series. You can buy 
    them in a strip for the purposes of developing them into code.
    
    LED Datasheet: https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
    
    Function Requirements:
    
        - We want 19 display LEDs in series. The first and last two are for
          warning lights. The central 15 are for rpm lights
          (see https://www.youtube.com/watch?v=u5kZjg_sJdg)
          
        - Two variables are passed to the function:
            -rpm (float(can be integer) - revs per minute of engine)
            -clt (float - coolant temperature)
            
        - Warning lights (clt value):
            - below 35 C - LEDs solid blue
            - Between 35 C and 100 C - LEDs off
            - between 100C and 107 C - LEDs solid red
            - Above 107 C - LEDs flashing red
            - Values are rough. Do some research to get more accurate
              information and link your sources. Contact me for engine 
              details
        
        - RPM lights (rpm value)
            - (left to right) 5 Green, 5 Red, 5 Blue
            - Threshold for each to turn on is a design choice you have to make 
              (do some research and produce a document as this scores points in 
              design presentation) Jonathan Collins is one of the best racers
              in Cambridge so speak to him if you want an idea.
            - Above 12500 ALL the LEDs flash blue (note do this via interrupts, 
              never use delays if possible)
             
////////////////////////////////////////////////////////////////////////////////

Telemetry Software: (INSERT NAME HERE)

    If you want to develop software that plots data in real-time in several
    different graph types message and I will make a detailed plan but it's
    the most difficult task. It is beyong my coding skills/understanding
    so you will be on your own. We have something that does this already so
    no-one feel obliged to work on it
    
////////////////////////////////////////////////////////////////////////////////

Read CAN function: (INSERT NAME HERE)

    Previous code worked perfectly fine but was very rigid and non adaptable.
    All ECUs have a tabulated form similar to:
    http://www.msextra.com/doc/pdf/Megasquirt_CAN_Broadcast.pdf
    As we are going to be working with different ECUs in the future and
    potentially this year, we want the code structured in a way so that we can
    easily modify a form of "table" in the code to change ECU.
    
    Note this will require access to an ECU to test so if you are in Cambridge
    I can sort out access for you but otherwise I am in Cambridge for summer
    so I can test it for you.
    
    See the README in the old code for documentation to get you going
    
    Function Requirements:
        
        - Solution not necessarily in a function form but rather write a body
          of code in which we will implement the other functions within
          
        - Rather than hard code each data field in if statements (what I did)
          have the code loop through a form of table
          https://github.com/hugohadfield/PycroSquirt?fbclid=IwAR2VfK3nLpm_gJR32rTgj_sBaHsmAMyxUEX0m65-PVn7jPGLHAkJ7-6FZCU
          This is an alumni's code which looped through a table on a text
          file when we were based on rasberry pi. Essetially what this is doing
          
        - Easy way to access each variable extracted to use in other functions

////////////////////////////////////////////////////////////////////////////////