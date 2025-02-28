// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Feb 22 16:13:58 2025
//  Last Modified : <250228.1451>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2025  Robert Heller D/B/A Deepwoods Software
///			51 Locke Hill Road
///			Wendell, MA 01379-9728
///
///    This program is free software; you can redistribute it and/or modify
///    it under the terms of the GNU General Public License as published by
///    the Free Software Foundation; either version 2 of the License, or
///    (at your option) any later version.
///
///    This program is distributed in the hope that it will be useful,
///    but WITHOUT ANY WARRANTY; without even the implied warranty of
///    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///    GNU General Public License for more details.
///
///    You should have received a copy of the GNU General Public License
///    along with this program; if not, write to the Free Software
///    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/// @file TinyArtClock.ino
///
/// Implements a colorful clock using NeoPixels and a KB2040. 
///
/// In the center is a single NeoPixel for the seconds indicator, with a 12
/// pixel ring for the hours and a 24 pixel ring for "minutes" -- the minutes
/// for this clock are 150 seconds long (2-1/2 regular minutes) -- the hour
/// is broken into 24 parts.
/// 
/// Each of the lit pixels cycle through the color wheel over the course of 
/// their period.  The seconds indicator shows ten colors over the course of 
/// one second.  The minutes pixel shows 150 colors over the course of 150
/// seconds.  And the hours pixel shows 24 colors over the course of an hour.
///
/// @author Robert Heller
/// @date Sat Feb 22 16:13:58 2025
///
/// 
///
//////////////////////////////////////////////////////////////////////////////

#include "Adafruit_NeoPixel.h"
#include <Button.h>

//#define SECONDSPIN 5
//#define NUMSECONDSPIXELS 1
//Adafruit_NeoPixel SecondsPixels(NUMSECONDSPIXELS,SECONDSPIN,NEO_GRB + NEO_KHZ800);
#define MINUTESPIN 6
#define NUMMINUTESPIXELS 24
Adafruit_NeoPixel MinutesPixels(NUMMINUTESPIXELS,MINUTESPIN,NEO_GRB + NEO_KHZ800);
#define HOURSPIN 7
#define NUMHOURSPIXELS 12
Adafruit_NeoPixel HoursPixels(NUMHOURSPIXELS,HOURSPIN,NEO_GRB + NEO_KHZ800);

Button SetMinutes(8);
Button SetHours(9);

#define DELAYVAL 10//0 // Run at 10x speed for test purposes.

#define NUMSECSCOLORS 10
uint32_t seccolors[NUMSECSCOLORS];
int tenths = 0;
int seconds = 0;
#define NUMMINUTESCOLORS 150
uint32_t mincolors[NUMMINUTESCOLORS];
int minutes = 0;
#define NUMHOURSCOLORS 24
uint32_t hrcolors[NUMHOURSCOLORS];
int hours = 0;

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel &strip, byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void setup() {
    // Initialize I/O
    //SecondsPixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    MinutesPixels.begin();
    HoursPixels.begin();
    SetMinutes.begin();
    SetHours.begin();
    
    // Initialize color lookup tables.
    int icolor;
    //for (icolor = 0; icolor < NUMSECSCOLORS; icolor++)
    //{
    //    byte colorindex = (((double)icolor)/(NUMSECSCOLORS-1))*255;
    //    seccolors[icolor] = Wheel(SecondsPixels,colorindex);
    //}
    for (icolor = 0; icolor < NUMMINUTESCOLORS; icolor++)
    {
        byte colorindex = (((double)icolor)/(NUMMINUTESCOLORS-1))*255;
        mincolors[icolor] = Wheel(MinutesPixels,colorindex);
    }
    for (icolor = 0; icolor < NUMHOURSCOLORS; icolor++)
    {
        byte colorindex = (((double)icolor)/(NUMHOURSCOLORS-1))*255;
        hrcolors[icolor] = Wheel(HoursPixels,colorindex);
    }
}


                
void loop() {
    // tick in 1/10s of a second.
    tenths++;
    if (tenths >= NUMSECSCOLORS) // overflow tenths, reset and bump seconds.
    {
        tenths = 0;
        seconds++;
        if (seconds >= NUMMINUTESCOLORS) // overflow seconds, reset and bump minutes
        {
            seconds = 0;
            minutes++;
            if (minutes >= NUMMINUTESPIXELS) // overflow minutes, reset and bump hours
            {
                minutes = 0;
                hours++;
                if (hours >= NUMHOURSPIXELS) // overflow hours, reset.
                {
                    hours = 0;
                }
            }
        }
    }
    if (SetMinutes.released()) // set minutes?
    {
        minutes++;
        if (minutes >= NUMMINUTESPIXELS)
        {
            minutes=0;
        }
    }
    if (SetHours.released()) // set hours?
    {
        hours++;
        if (hours >= NUMHOURSPIXELS)
        {
            hours = 0;
        }
    }
    // update display
    //SecondsPixels.clear(); // Set all pixel colors to 'off'
    //SecondsPixels.setPixelColor(0, seccolors[tenths]);
    //SecondsPixels.show();   // Send the updated pixel colors to the hardware.
    MinutesPixels.clear(); // Set all pixel colors to 'off'
    MinutesPixels.setPixelColor((minutes+1)%NUMMINUTESPIXELS, mincolors[seconds]);
    MinutesPixels.show();
    HoursPixels.clear(); // Set all pixel colors to 'off'
    HoursPixels.setPixelColor(hours, hrcolors[minutes]);
    HoursPixels.show();
    // next tick
    delay(DELAYVAL); // Pause before next pass through loop
}    
