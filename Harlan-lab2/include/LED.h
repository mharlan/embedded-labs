#ifndef LED_H
#define LED_H

/*
	Initialize the LED display.
	
	Performs timer setup and displays blank spaces.
 */
void init_leds(void);

/*
	Updates the LEDs.
 */
void led_update(void);

/*
 	Set the scroll timer cutoff in seconds.
 */
void led_set_timer_cutoff(float seconds);

/*
	Switch the LEDs to text display mode and display msg.
 */
void led_display_text(const unsigned char *msg);

/*
	Display a floating point number out to 8 digits.
	Switches to text mode.
 */
void led_display_float(float value);

/*
	Sets an int value to the display and switches
	to text mode.
 */
void led_display_int(int value);

/*
	Sets an int hex value to the display and
	switches to text mode.
 */
void led_display_int_hex(int value);

#endif