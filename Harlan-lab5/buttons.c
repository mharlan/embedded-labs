#include "buttons.h"
#include "timer.h"
#include "macro.h"

#include <zneo.h>

#define DEBOUNCE_CUTOFF     40 	//40 ms
#define BUTTON_TWICE_CUTOFF 500	//500 ms

#define BUTTON_NONE  0xC8
#define BUTTON_ONE   0xC0
#define BUTTON_TWO   0x88
#define BUTTON_THREE 0x48

#define BUTTON_PRESSED     1
#define BUTTON_NOT_PRESSED 0

static volatile int button_timer;
static int debounce_cutoff;
static volatile int button_twice_timer;
static int button_twice_cutoff;

static volatile unsigned char last_button;
static volatile unsigned char current;
static volatile unsigned char previous;
static volatile unsigned short button_state;

static void handle_button_events(void);

/*
	Initializes the buttons.
 */
void init_buttons(void)
{
	//set as inputs
	PDDD |= BUTTON_ONE;
	PFDD |= BUTTON_TWO + BUTTON_THREE;

	current = BUTTON_NONE;
	previous = BUTTON_NONE;
	button_state = BUTTON_NOT_PRESSED;
	last_button = BUTTON_NONE;

	button_timer = 0;
	debounce_cutoff = DEBOUNCE_CUTOFF;

	button_twice_timer = 0;
	button_twice_cutoff = BUTTON_TWICE_CUTOFF;
}

/*
	Processes button events.
 */
void button_events(void)
{
	button_timer += timer_interval_int();

	if(button_twice_timer >= button_twice_cutoff) {
		button_twice_timer = 0;
		last_button = BUTTON_NONE;
	}
	else if(button_twice_timer > 0) {
		button_twice_timer += timer_interval_int();
	}

	//check buttons every debounce interval
	if(button_timer >= debounce_cutoff) {
		button_timer = 0;
		
		previous = current;
		current = (PDIN & 0x08) | (PFIN & 0xC0);	//gets the state of all buttons
		
		if(current == previous) {
			if(current != BUTTON_NONE) {
				if(button_state == BUTTON_NOT_PRESSED) {
					button_state = BUTTON_PRESSED;
					handle_button_events();
				}
			}
			else if(button_state == BUTTON_PRESSED) {
				button_twice_timer += timer_interval_int();
				button_state = BUTTON_NOT_PRESSED;
			}
		}
	}
}

/*
	Handles the button event.
 */
static void handle_button_events(void)
{
	if(current == BUTTON_ONE) {
		if(button_twice_timer && (last_button == BUTTON_ONE)) {
			button_twice_timer = 0;
			last_button = BUTTON_NONE;
		}
		else {
			last_button = BUTTON_ONE;

			macro_execute(MACRO0);
		}
	}
	else if(current == BUTTON_TWO) {
		if(button_twice_timer && (last_button == BUTTON_TWO)) {
			button_twice_timer = 0;
			last_button = BUTTON_NONE;
		}
		else {
			last_button = BUTTON_TWO;

			macro_execute(MACRO1);
		}
	}
	else if(current == BUTTON_THREE) {
		if(button_twice_timer && (last_button == BUTTON_THREE)) {
			button_twice_timer = 0;
			last_button = BUTTON_NONE;
		}
		else {
			last_button = BUTTON_THREE;

			macro_execute(MACRO2);
		}
	}
	//don't do anything if multiple buttons are pressed
	else {
		button_state = BUTTON_NOT_PRESSED;
	}
}
