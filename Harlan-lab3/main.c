/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	Class:  CSCI-4415
	Date: 	March 1st, 2011
	Lab:    3
	
	Description: This program is a command line interface that communicates via
	a serial port. Run the program and enter "?" to see a list of available commands.

	Other files: buttons.c buttons.h cli.c cli.h info.c info.h LED.c LED.h LED_ascii.h
	macro.c macro.h oscillator.c oscillator.h ports.c ports.h timer.c timer.h uart.c uart.h

	Compile: Set the user include path to the include directory.
	
	Problems: I could not get access to ports J or K.

	Comments: None.

	Enhancements: Transfers and receives over the UART using interrupts and buffers.
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

	//initialize the command line interface
	init_cli();

	//initialize button functionality
	init_buttons();

	//enable interrupts
	EI();

	cli_loop();
}