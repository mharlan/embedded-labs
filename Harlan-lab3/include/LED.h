#ifndef __LED_H
#define __LED_H

/*
	Initialize the LED display.
	
	Performs timer setup and displays blank spaces.
 */
extern void init_leds(void);

/*
	Updates the LEDs.
 */
extern void led_update(void);

/*
 	Set the scroll timer cutoff in milliseconds.
 */
extern void led_set_scroll_cutoff(int ms);

/*
	Switch the LEDs to text display mode and display msg.
 */
extern void led_display_text(const unsigned char *msg);

/*
	Display a floating point number out to 8 digits.
	Switches to text mode.
 */
extern void led_display_float(float value);

/*
	Sets an int value to the display and switches
	to text mode.
 */
extern void led_display_int(int value);

/*
	Sets an int hex value to the display and
	switches to text mode.
 */
extern void led_display_int_hex(int value);

#endif