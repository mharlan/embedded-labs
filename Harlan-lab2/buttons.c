#include "buttons.h"
#include "LED.h"
#include "LED_interrupts.h"
#include "ringtones.h"
#include "rttl.h"
#include "speaker.h"

#include <zneo.h>

float button_timer;
float debounce_cutoff;

float button_twice_timer;
float button_twice_cutoff;

unsigned char last_button;
static unsigned char current;
static unsigned char previous;
static unsigned short button_state;

static void handle_button_events(void);

void init_buttons(void)
{
	//set as inputs
	PDDD |= BUTTON_ONE;
	PFDD |= BUTTON_TWO + BUTTON_THREE;

	current = BUTTON_NONE;
	previous = BUTTON_NONE;
	button_state = BUTTON_NOT_PRESSED;
	last_button = BUTTON_NONE;
}

void button_events(void)
{
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
			button_twice_timer += DRAW_TIME;
			button_state = BUTTON_NOT_PRESSED;
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
			stop_ringtone();
		}
		else {
			last_button = BUTTON_ONE;
			play_rttl_ringtone(zelda);
		}
	}
	else if(current == BUTTON_TWO) {
		if(button_twice_timer && (last_button == BUTTON_TWO)) {
			button_twice_timer = 0;
			last_button = BUTTON_NONE;

			stop_ringtone();
		}
		else {
			last_button = BUTTON_TWO;
			play_rttl_ringtone(starwars);
		}
	}
	else if(current == BUTTON_THREE) {
		if(button_twice_timer && (last_button == BUTTON_THREE)) {
			button_twice_timer = 0;
			last_button = BUTTON_NONE;

			stop_ringtone();
		}
		else {
			last_button = BUTTON_THREE;
			play_rttl_ringtone(bohemian);
		}
	}
	//don't do anything if multiple buttons are pressed
	else {
		button_state = BUTTON_NOT_PRESSED;
	}
}