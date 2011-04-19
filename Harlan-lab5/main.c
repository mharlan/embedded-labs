/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	Class:  CSCI-4415
	Date: 	March 29th, 2011
	Lab:    5
	
	Description: This program extends the command line interface with i2c and SPI functionality. Keyboard 
	and speaker functionality has been removed for space reasons from this release.

	Other files: buttons.c buttons.h cli.c cli.h info.c info.h LED.c LED.h LED_ascii.h
	macro.c macro.h oscillator.c oscillator.h ports.c ports.h timer.c timer.h uart.c uart.h
	i2c.h i2c.c spi.h spi.c 24lc16b.h 24lc16b.c 25lc040a.h 25lc040a.c delay.h delay.c

	Compile: Set the user include path to the include directory.
	
	Problems: I forgot to connect WP on the 24lc16b to ground and proceeded to debug this
	for two hours, only to find out the software was correct.

	Comments: Very helpful lab.

	Enhancements: None.
 */

#include "LED.h"
#include "oscillator.h"
#include "buttons.h"
#include "timer.h"
#include "cli.h"
#include "macro.h"

#include <zneo.h>
#include <stdio.h>

/*
	Intializes the LED, sets the default value, and loops.
 */
void main(void)
{
	//initialize the oscillator and global timer
	init_oscillator(OSC_5_52MHZ);
	init_timer(TIMER_2MS);

	//initialize button functionality
	init_buttons();

	//initialize the command line interface
	init_cli();

	//enable interrupts
	EI();

	cli_loop();
}