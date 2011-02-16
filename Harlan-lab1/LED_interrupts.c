#include "timer.h"
#include "buttons.h"
#include "matrix.h"
#include "LED.h"
#include "LED_interrupts.h"

#include <zneo.h>
#include <stdio.h>
#include <string.h>

#define LED_DEC_MAX  9999
#define LED_HEX_MAX  0xFFFF

#define NUM_ANODES   7
#define D1           0
#define D2           1
#define D3           2
#define D4           3

unsigned char *led_msg;
size_t msg_size;

unsigned int draw_char[NUM_LEDS];
unsigned int msg_pos;
unsigned int row_pos;
unsigned int led_state;
unsigned int uptime_state;

float uptime;
float timer;
float timer_cutoff;

extern float button_timer;
extern float debounce_cutoff;

extern float button_twice_timer;
extern float button_twice_cutoff;

extern unsigned char last_button;

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

static void led_draw(unsigned int led_id);
static void init_led_draw_timer(void);

void init_led_timers(void)
{
	// unlock the oscillator control register
	OSCCTL = 0xE7; OSCCTL = 0x18;

	// A0 = 1010_0000 = internal 5.52 MHz
	OSCCTL = 0xA0;

	//setup timing variables
	timer = 0;
	uptime = 0;
	timer_cutoff = SCROLL_CUTOFF;

	button_timer = 0;
	debounce_cutoff = DEBOUNCE_CUTOFF;

	button_twice_timer = 0;
	button_twice_cutoff = BUTTON_TWICE_CUTOFF;

	//set LED display defaults
	led_state = LED_TEXT;
	uptime_state = UPTIME_DEC;
	led_msg = NULL;

	msg_size = 0;
	draw_char[0] = ASCII_SPACE;
	draw_char[1] = ASCII_SPACE;
	draw_char[2] = ASCII_SPACE;
	draw_char[3] = ASCII_SPACE;

	init_led_draw_timer();
}

/*
	Interrupt for updating the LED.

	This interrupt also handles button events via timed
	polling.
 */
void interrupt draw_timer_isr(void)
{
	unsigned int led_uptime;

	//increment timers
	timer += DRAW_TIME;
	uptime += DRAW_TIME;
	button_timer += DRAW_TIME;

	if(button_twice_timer >= button_twice_cutoff) {
		button_twice_timer = 0;
		last_button = BUTTON_NONE;
	}
	else if(button_twice_timer > 0) {
		button_twice_timer += DRAW_TIME;
	}

	//updates the characters being displayed at timer_cutoff interval
	if(timer >= timer_cutoff) {
		timer = 0;

		if(led_state == LED_UPTIME_S || led_state == LED_UPTIME_MS) {
			led_uptime = (unsigned int)((led_state == LED_UPTIME_S) ? (uptime / 1.0) : (uptime / 0.001));
						
			if(uptime_state == UPTIME_DEC) {
				if(led_uptime > LED_DEC_MAX) {
					led_uptime = LED_DEC_MAX;
				}
				
				led_set_int(led_uptime);
			}
			else if(uptime_state == UPTIME_HEX) {
				if(led_uptime > LED_HEX_MAX) {
					led_uptime = LED_HEX_MAX;
				}
					
				led_set_int_hex(led_uptime);
			}
		}

		//update what each led is drawing
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

		//scroll if necessary
		if(msg_size > 4) {
			msg_pos = (msg_pos + 1) % msg_size;
		}
	}

	//draw the current row for each LED
	led_draw(D1);
	led_draw(D2);
	led_draw(D3);
	led_draw(D4);

	//move to the next row for next time
	row_pos = (row_pos + 1) % NUM_ANODES;

	//check buttons every debounce interval
	if(button_timer >= debounce_cutoff) {
		button_timer = 0;
		button_events();
	}
}

/*
 	Draws the current row to a particular LED
 */
static void led_draw(unsigned int led_id)
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
	Initialize the millisecond timer.
 */
static void init_led_draw_timer(void)
{
	T0CTL1 |= TIMER_DISABLE;

    T0CTL1 = TIMER_MODE_CONTINUOUS + TIMER_PRESCALE_128;

    // Initial counter value
    T0HL = 0x00;

    // Timer reload
    //   reload = clock / prescale * timeout  
    T0R = CLOCK / 128 * DRAW_TIME;

	// Enable Timer0 interrupt
    IRQ0EN = IRQ_Timer0;

	T0CTL1 |= TIMER_ENABLE;

	SET_VECTOR(TIMER0, draw_timer_isr);
}
