#ifndef LED_INTERRUPTS_H
#define LED_INTERRUPTS_H

#define ASCII_SPACE  0
#define ASCII_OFFSET 0x20
#define NUM_LEDS     4

//time in seconds
#define DRAW_TIME     0.002
#define SCROLL_CUTOFF 0.4
#define MS_CUTOFF     0.014
#define SECOND_CUTOFF 1.0

#define LED_TEXT      0
#define LED_UPTIME_S  1
#define LED_UPTIME_MS 2

#define UPTIME_DEC 0
#define UPTIME_HEX 1

/*
 	Initialize the LED timer and drawing interrupt.

	Default is text draw mode.
 */
void init_led_timers(void);

#endif