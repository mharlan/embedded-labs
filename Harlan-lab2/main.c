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

	Other files: [list other files that are necessary for this program]

	Compile: [provide any special instructions for compiling. Only necessary if 
	there are special instructions]
	
	Problems: [explaining what you did, what problems you had, how you solved them, 
	and what you might do differently if you had to do it again]

	Comments: [Feel free to provide comments on how this lab went, what you think 
	is good or bad about it and how it could be improved or anything else you want 
	to say.]

	Enhancements: [describe the enhancements you added to this lab]
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