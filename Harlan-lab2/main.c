
#include "LED.h"
#include "buttons.h"
#include "speaker.h"

#include <zneo.h>

/*
	Intializes the LED, sets the default value, and loops.
 */
void main(void)
{
	init_buttons();
	init_speaker();
	led_init();

	//enable interrupts
	EI();

	//run forever
	while(1) {
		//do nothing while responding to interrupts
	}
}