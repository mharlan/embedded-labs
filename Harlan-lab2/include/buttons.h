#ifndef BUTTONS_H
#define BUTTONS_H

#define DEBOUNCE_CUTOFF     0.040 	//40 ms
#define BUTTON_TWICE_CUTOFF 0.5		//500 ms

#define BUTTON_NONE  0xC8
#define BUTTON_ONE   0xC0
#define BUTTON_TWO   0x88
#define BUTTON_THREE 0x48

#define BUTTON_PRESSED     1
#define BUTTON_NOT_PRESSED 0

/*
	Initializes the buttons.
 */
void init_buttons(void);

/*
	Processes button events.
 */
void button_events(void);

#endif