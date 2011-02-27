#include "LED.h"
#include "LED_ascii.h"
#include "timer.h"

#include <zneo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ASCII_SPACE  0
#define ASCII_OFFSET 0x20
#define NUM_LEDS     4

//time in seconds
#define SCROLL_CUTOFF 400

#define LED_DEC_MAX  9999
#define LED_HEX_MAX  0xFFFF

#define NUM_ANODES   7
#define D1           0
#define D2           1
#define D3           2
#define D4           3

#define MAX_DIGITS 16  //Max digits for number displayed on LED

static unsigned char *led_msg;
static size_t msg_size;

static unsigned int draw_char[NUM_LEDS];
static volatile unsigned int msg_pos;
static volatile unsigned int row_pos;

static volatile int led_scroll_timer;
static int led_scroll_cutoff;

//values for selecting each LED row
static unsigned int led_anode[NUM_ANODES] =
{
	0x01,
	0x02,
	0x04,
	0x08,
	0x10,
	0x20,
	0x40
};

static void led_scroll_draw_chars(void);
static void led_set_draw_chars(void);
static void led_draw_row(int led_id);

void init_leds(void) 
{ 
    PEDD = 0x00;	// data direction = outputs	
	PGDD = 0x00;

	led_scroll_timer = 0;
	led_scroll_cutoff = SCROLL_CUTOFF;

	//set LED display defaults
	led_msg = NULL;

	msg_size = 0;
	draw_char[0] = ASCII_SPACE;
	draw_char[1] = ASCII_SPACE;
	draw_char[2] = ASCII_SPACE;
	draw_char[3] = ASCII_SPACE;
}

void led_update(void)
{
	led_scroll_timer += timer_interval_int();

	//updates the characters being displayed at timer_cutoff interval
	if((msg_size > 4) && 
	   (led_scroll_timer >= led_scroll_cutoff)) {
		led_scroll_timer = 0;

		led_scroll_draw_chars();
	}

	//draw the current row for each LED
	led_draw_row(D1);
	led_draw_row(D2);
	led_draw_row(D3);
	led_draw_row(D4);

	//move to the next row for next time
	row_pos = (row_pos + 1) % NUM_ANODES;
}

void led_set_scroll_cutoff(int ms)
{
	led_scroll_cutoff = ms;
}

void led_display_text(const unsigned char *msg)
{
	char *new_msg;

	msg_size = strlen(msg);
	new_msg = malloc(sizeof(*new_msg) * (msg_size + 2));	//+2 for space pad and null terminator
	if(!new_msg) {
		msg_size = 0;
	}
	else {
		memcpy(new_msg, msg, msg_size);

		//space pads the wrap-around
		if(msg_size > 4) {
			new_msg[msg_size] = ' ';
			++msg_size;
		}
		new_msg[msg_size] = '\0';

		DI();
		
		if(led_msg != NULL) {
			free(led_msg);
		}
		
		led_msg = new_msg;
		msg_pos = 0;
		row_pos = 0;
		led_set_draw_chars();

		EI();
	}
}

void led_display_double(double value)
{
	unsigned char num_msg[MAX_DIGITS];

	sprintf(num_msg, "%f", value);

	led_display_text(num_msg);
}

void led_display_int(int value)
{
	unsigned char num_msg[MAX_DIGITS];

	sprintf(num_msg, "%d", value);

	led_display_text(num_msg);
}

void led_display_int_hex(int value)
{
	unsigned char num_msg[MAX_DIGITS];

	sprintf(num_msg, "%X", value);

	led_display_text(num_msg);
}

/*
 	Draws the current row to a particular LED
 */
static void led_draw_row(int led_id)
{
	// set cathodes
	PEOUT |= 0x1F;
	PEOUT &= ~char_data[draw_char[led_id]][row_pos];

	// set anodes
	PGOUT &= 0x80;
	PGOUT |= led_anode[row_pos];

	//latch the LED
	if(led_id == D1) {               // PE7 controls D1
        PEOUT &= ~0x80;           //   create rising edge on PE7, clear bit 7
        PEOUT |= 0x80;            //   set bit 7
    }
    else if(led_id == D2) {               // PG7 controls D2
        PGOUT &= ~0x80;           //   create rising edge on PG7
        PGOUT |= 0x80; 
    }
    else if(led_id == D3) {               // PE5 controls D3
        PEOUT &= ~0x20;           //   create rising edge on PE5
        PEOUT |= 0x20; 
    }
    else if(led_id == D4) {               // PE6 controls D4
        PEOUT &= ~0x40;           //   create rising edge on PE6
        PEOUT |= 0x40; 
    }
}

/*
	Updates what characters the LED is drawing.
 */
static void led_scroll_draw_chars(void)
{
	//update what each led is drawing
	draw_char[0] = ((unsigned int)led_msg[msg_pos]) - ASCII_OFFSET;
	draw_char[1] = ((unsigned int)led_msg[(msg_pos + 1) % msg_size]) - ASCII_OFFSET;
	draw_char[2] = ((unsigned int)led_msg[(msg_pos + 2) % msg_size]) - ASCII_OFFSET;
	draw_char[3] = ((unsigned int)led_msg[(msg_pos + 3) % msg_size]) - ASCII_OFFSET;
	msg_pos = (msg_pos + 1) % msg_size;
}

/*
	Sets the characters the LED is drawing to the first 4 of the message.
 */
static void led_set_draw_chars(void)
{
	if(msg_size > 0) {
		draw_char[0] = ((unsigned int)led_msg[msg_pos]) - ASCII_OFFSET;
	}
	else {
		draw_char[0] = ASCII_SPACE;
	}
	
	if(msg_size > 1) {
		draw_char[1] = ((unsigned int)led_msg[(msg_pos + 1) % msg_size]) - ASCII_OFFSET;
	}
	else {
		draw_char[1] = ASCII_SPACE;
	}
	
	if(msg_size > 2) {
		draw_char[2] = ((unsigned int)led_msg[(msg_pos + 2) % msg_size]) - ASCII_OFFSET;
	}
	else {
		draw_char[2] = ASCII_SPACE;
	}
	
	if(msg_size > 3) {
		draw_char[3] = ((unsigned int)led_msg[(msg_pos + 3) % msg_size]) - ASCII_OFFSET;
	}
	else {
		draw_char[3] = ASCII_SPACE;
	}
}
