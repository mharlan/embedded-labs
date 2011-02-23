/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	Class:  CSCI-4415
	Date: 	February 22nd, 2011
	Lab:    2
	
	Description: This program plays three RTTL ringtones. Ringtones are
	selected by pressing the buttons. The ringtone will loop with a one
	measure rest between each playthrough until a button is double tapped.
	The currently playing note and its duration is displayed on the LCD.

	Other files: buttons.c buttons.h LED.c LED.h notes.h oscillator.c oscillator.h ringtones.h
	rttl.c rttl.h speaker.c speaker.h timer.c timer.h

	Compile: Set the user include path to the include directory.
	
	Problems: I didn't run in to any significant problems.

	Comments: Another fun and challenging lab.

	Enhancements: None.
 */

#include "LED.h"
#include "oscillator.h"
#include "buttons.h"
#include "speaker.h"
#include "timer.h"

#include <zneo.h>

/*
	Intializes the LED, sets the default value, and loops.
 */
void main(void)
{
	//initialize the hardware
	init_buttons();
	init_speaker();
	init_leds();

	//initialize the oscillator and global timer
	init_oscillator(OSC_5_52MHZ);
	init_timer(TIMER_2MS);

	//enable interrupts
	EI();

	//run forever
	while(1) {
		//do nothing while responding to interrupts
	}
}