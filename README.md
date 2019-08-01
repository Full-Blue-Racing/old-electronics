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
    
    Function Description:
    
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
