/*
	Author: [Your name]
	Email:  [Your email]
	Class:  [CSCI-4415]
	Date: 
	Lab:    [Lab number]
	
	Description: [short description of program. Include changes you made and     
	note any enhancements that you made to the lab]
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
#include "interrupts.h"

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