#include "LED.h"
#include "LED_interrupts.h"

#include <zneo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 16  //Max digits for number displayed on LED

extern unsigned char *led_msg;
extern size_t msg_size;

extern unsigned int msg_pos;
extern unsigned int row_pos;
extern unsigned int led_state;
extern unsigned int uptime_state;

extern float timer_cutoff;

void led_set_text(const unsigned char *msg)
{
	if(led_msg != NULL) {
		free(led_msg);
	}

	msg_size = strlen(msg);
	led_msg = malloc(sizeof(*led_msg) * (msg_size + 2));	//+2 for space pad and null terminator
	if(!led_msg) {
		msg_size = 0;
	}
	else {
		memcpy(led_msg, msg, msg_size);

		//space pads the wrap-around
		if(msg_size > 4) {
			led_msg[msg_size] = ' ';
			++msg_size;
		}
	}
	led_msg[msg_size] = '\0';

	msg_pos = 0;
	row_pos = 0;
}

void led_display_text(const unsigned char *msg)
{
	led_state = LED_TEXT;
	led_set_timer_cutoff(SCROLL_CUTOFF);

	led_set_text(msg);
}

void led_set_timer_cutoff(float seconds)
{
	timer_cutoff = seconds;
}

void led_display_uptime_seconds(void)
{
	led_set_timer_cutoff(SECOND_CUTOFF);
	led_state = LED_UPTIME_S;
	uptime_state = UPTIME_DEC;
}

void led_display_uptime_ms(void)
{
	led_set_timer_cutoff(MS_CUTOFF);
	led_state = LED_UPTIME_MS;
	uptime_state = UPTIME_DEC;
}

void led_display_uptime_seconds_hex(void)
{
	led_set_timer_cutoff(SECOND_CUTOFF);
	led_state = LED_UPTIME_S;
	uptime_state = UPTIME_HEX;
}

void led_display_uptime_ms_hex(void)
{
	led_set_timer_cutoff(MS_CUTOFF);
	led_state = LED_UPTIME_MS;
	uptime_state = UPTIME_HEX;
}

void led_display_double(double value)
{
	led_state = LED_TEXT;
	led_set_timer_cutoff(SCROLL_CUTOFF);

	led_set_double(value);
}

void led_set_double(double value)
{
	unsigned char num_msg[MAX_DIGITS];

	sprintf(num_msg, "%f", value);

	led_set_text(num_msg);
}


void led_display_int(int value)
{
	led_state = LED_TEXT;
	led_set_timer_cutoff(SCROLL_CUTOFF);

	led_set_int(value);
}

void led_set_int(int value)
{
	unsigned char num_msg[MAX_DIGITS];

	sprintf(num_msg, "%d", value);

	led_set_text(num_msg);
}

void led_display_int_hex(int value)
{
	led_state = LED_TEXT;
	led_set_timer_cutoff(SCROLL_CUTOFF);

	led_set_int_hex(value);
}

void led_set_int_hex(int value)
{
	unsigned char num_msg[MAX_DIGITS];

	sprintf(num_msg, "%X", value);

	led_set_text(num_msg);
}

void led_init(void) 
{ 
    PEDD = 0x00;	// data direction = outputs	
	PGDD = 0x00;

	init_led_timers();
}
