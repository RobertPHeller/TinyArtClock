# Tiny Art Clock
Implements a colorful clock using NeoPixels and a KB2040. 

In the center is a single NeoPixel for the seconds indicator, with a 12
pixel ring for the hours and a 24 pixel ring for "minutes" -- the minutes
for this clock are 150 seconds long (2-1/2 regular minutes) -- the hour
is broken into 24 parts.
 
Each of the lit pixels cycle through the color wheel over the course of 
their period.  The seconds indicator shows ten colors over the course of 
one second.  The minutes pixel shows 150 colors over the course of 150
seconds.  And the hours pixel shows 24 colors over the course of an hour.

- Front (face) ![Front](https://github.com/RobertPHeller/TinyArtClock/blob/main/Images/front_cropped.jpg)
- Back (electronics) ![Back](https://github.com/RobertPHeller/TinyArtClock/blob/main/Images/back_cropped.jpg)
- Video [Video](https://youtu.be/39Z0Mqmfn8U)
