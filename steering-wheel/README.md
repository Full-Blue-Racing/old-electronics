# Steering Wheel LEDs: Ashley & Antonis?

On the steering wheel we have rpm LEDs and indicator LEDs, previously
they were fixed colour LEDs and each one had its own pin on the arduino to 
drive it. This year we want to switch to using WS2812B LEDs (you can find a 
better/ alternative solutions, these are just common) They are RGB LEDs that
are controlled by clocking information through them in series. You can buy 
them in a strip for the purposes of developing them into code.
    
[Link to LED Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf)
    
## Function Requirements:
    
1. We want 19 display LEDs in series. The first and last two are for
   warning lights. The central 15 are for rpm lights
   (see [https://www.youtube.com/watch?v=u5kZjg_sJdg])
  
2. Two variables are passed to the function:
    -rpm (float(can be integer) - revs per minute of engine)
    -clt (float - coolant temperature)
    
3. Warning lights (clt value):
    - below 35 C - LEDs solid blue
    - Between 35 C and 100 C - LEDs off
    - between 100C and 107 C - LEDs solid red
    - Above 107 C - LEDs flashing red
    - Values are rough. Do some research to get more accurate
      information and link your sources. Contact me for engine 
      details

4. RPM lights (rpm value):
    - (left to right) 5 Green, 5 Red, 5 Blue
    - Threshold for each to turn on is a design choice you have to make 
      (do some research and produce a document as this scores points in 
      design presentation) Jonathan Collins is one of the best racers
      in Cambridge so speak to him if you want an idea.
    - Above 12500 ALL the LEDs flash blue (note do this via interrupts, 
      never use delays if possible)

# Steering Wheel Screen: (Insert Name 1 & Name 2 & Name 3 here)

previously we used a screen driven directly via an arduino nano. The problem
was that the arduino was 8-Bit so this meant it lacked the speed to update the
screen smoothly enough to do graphics (could only do text).

This means we have switched to using a Nextion screen:
[Link to Nextion Webside](https://nextion.itead.cc/)

These are seperate microprocessor/screen units that operate at 32-bit. Allowing
graphical displays. They work by communicating via serial to an arduino in the 
steering wheel that is pulling data off the CAN bus.

## Functional Requirements:

1. Decide on which Model to use. There are multiple options so take a look
   at each of the different series and document the option you went for. In 
   terms of size to choose, last year we went with a 3.5" screen and I can
   send photos/CAD of that to give you an idea of size relative to the steering
   wheel. We are going to be reusing the same shape of the centre of the
   wheel so a step down to the 3.2" screen is an idea to play with. Best thing
   to do is play around with CAD and see what will fit with the extra LEDs that
   are going to be at the side of the screen (look at an f1 steering wheel)

2. One of the buttons on the steering wheel will be used to toggle through the
   different screen display modes:
    - Driver Mode
    - Data Mode
    - Standby Mode

3. Keep in mind visibility in the sun and the fact the driver is shaken
   around a lot

4. Driver Mode:
    - Contains a central RPM dial similar to that in cars
    - Clear temperature readoff for clt (coolant temp)
    - Keep in mind the steering wheel tilts when turned when designing
      graphics
    - Display showing gear that you are in (bug me to add this to the car)
    - Other parameters may be added

5. Data Mode:
    - Display all the datafields received over CAN bus in a clear format
    - Might need to display over multiple screens but that is fine

6. Standby Mode:
    - Simply display an image on the screen, if possible a GIF or most desirably
      a Video

# Steering Wheel PCB: (Insert name here)

We need to connect all these components together on the steering wheel. This
will require a complex (multi-layer) PCB to connect them together. This will 
require CAD skills as well. 

## Functional requirements (To do):

1. Get a full spec list of everything to connect together:
    - Schematics for connections
    - CAD models of each component

2. Design a multi-layer PCB:
    - Will need to design as seperate projects in KiCad
    - Have to consider layout of LEDs and buttons (need to choose buttons)
    - We want to be able to modify the code on the device so make it possibe to access programming ports/ add external connector
    - Include mounting holes and design how it is supposed to be assembled together

3. Produce an accurate CAD model of each of the parts and an assembly of the whole thing together
    - !!!No incomplete constraints!!!