#ifndef LED_H
#define LED_H

/*
	Initialize the LED display.
	
	Performs timer setup and displays blank spaces.
 */
void led_init(void);

/*
 	Set the scroll timer cutoff in seconds.
 */
void led_set_timer_cutoff(float seconds);

/*
	Switch the LEDs to text display mode and display msg.
 */
void led_display_text(const unsigned char *msg);

 /*
	Set the display message without switching modes.
 */
void led_set_text(const unsigned char *msg);

/*
	Display how long the program has been running in
	seconds on the LEDs.

	Switches to uptime seconds mode.
 */
void led_display_uptime_seconds(void);

/*
	Display how long the program has been running in
	seconds in hexidecimal notation on the LEDs.

	Switches to uptime seconds mode.
 */
void led_display_uptime_seconds_hex(void);

/*
	Display how long the program has been running in
	milliseconds on the LEDs.

	Switches to uptime millisecond mode.
 */
void led_display_uptime_ms(void);

/*
	Display how long the program has been running in
	milliseconds in hexidecimal notation on the LEDs.

	Switches to uptime millisecond mode.
 */
void led_display_uptime_ms_hex(void);

/*
	Display a floating point number out to 8 digits.
	Switches to text mode.
 */
void led_display_double(double value);


/*
	Sets a double value to the display without
	switching modes.
 */
void led_set_double(double value);

/*
	Sets an int value to the display and switches
	to text mode.
 */
void led_display_int(int value);

/*
	Sets an int value to the display without
	switching modes.
 */
void led_set_int(int value);

/*
	Sets an int hex value to the display and
	switches to text mode.
 */
void led_display_int_hex(int value);

/*
	Sets an int hex value to the display without
	switching modes.
 */
void led_set_int_hex(int value);

#endif