/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	Class:  CSCI-4415
	Date: 	March 22nd, 2011
	Lab:    4
	
	Description: This program extends the command line interface with PS/2 keyboard functionality.

	Other files: buttons.c buttons.h cli.c cli.h info.c info.h LED.c LED.h LED_ascii.h
	macro.c macro.h oscillator.c oscillator.h ports.c ports.h timer.c timer.h uart.c uart.h
	notes.h speaker.h speaker.c ps2_port.c ps2_port.h scancodes.h keyboard.c keyboard.h

	Compile: Set the user include path to the include directory.
	
	Problems: None.

	Comments: None.

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