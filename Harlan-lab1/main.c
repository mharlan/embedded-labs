/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	Class:  CSCI-4415
	Date: 	2/14/2011
	Lab:    1

	Description: "Hello World from ZNEO" scrolls across the LEDs on startup.
	Pressing buttons changes what is displayed on the LEDs.

	Button 1 Once: Uptime in seconds. Stops at 9999 Seconds.
	Button 1 Twice: Uptime in milliseconds. Stops at 9999 ms.
	Button 2 Once: PI to 8 digits.
	Button 2 Twice: Uptime in seconds in hex. Stops at FFFF seconds.
	Button 3 Once: "Hello World"
	Button 3 Twice: "Matthew Harlan CSCI 4415"

	Other files: buttons.c buttons.h LED.c LED.h LED_interrupts.c LED_interrupts.h main.c matrix.h timer.h

	Compile: Standard C Libary (for malloc and sprintf)

	Problems: I intially tried to do this with multiple interrupts and timers. I had trouble getting
	the other timer interrupt to trigger. Switching it over to one timer was conceptually difficult at first,
	but once I got it all setup it made a lot more sense for this situation.

	Comments: It was a fun and challenging lab. I learned a lot.

	Enhancements: None.
*/

#include "LED.h"
#include "buttons.h"

#include <zneo.h>

/*
	Intializes the LED, sets the default value, and loops.
 */
void main(void)
{
	init_buttons();
	led_init();
	led_display_text("Hello World from ZNEO");

	//enable interrupts
	EI();

	//run forever
	while(1) {
		//do nothing while responding to interrupts
	}
}