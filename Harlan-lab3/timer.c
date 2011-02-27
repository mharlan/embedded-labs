#include "timer.h"
#include "oscillator.h"
#include "LED.h"
#include "buttons.h"

#include <zneo.h>

#define INTERVAL_1MS_INT 1
#define INTERVAL_2MS_INT 2
#define INTERVAL_4MS_INT 4

#define INTERVAL_1MS_FLOAT 0.001f
#define INTERVAL_2MS_FLOAT 0.002f
#define INTERVAL_4MS_FLOAT 0.004f

static int timer_state;

/*
	Interrupt for timer events.

	Used for updating the LED, polling the buttons, and responding
	to note change events for the speaker..
 */
void interrupt timer_isr(void)
{
	//enable interrupts for speaker interrupt
	EI();

	led_update();
	button_events();
}

void init_timer(int mode)
{
	timer_state = mode;

	T0CTL1 |= TIMER_DISABLE;
    T0CTL1 = TIMER_MODE_CONTINUOUS + TIMER_PRESCALE_128;

    // Initial counter value
    T0HL = 0x00;

	if(timer_state == TIMER_4MS) {
		// Timer reload
    	//   reload = clock / prescale * timeout  
   	 	T0R = (get_osc_clock() / 128) * INTERVAL_4MS_FLOAT;
	}
	else if(timer_state == TIMER_1MS) {
		T0R = (get_osc_clock() / 128) * INTERVAL_1MS_FLOAT;
	}
	//default timer is 2ms
	else {
		T0R = (get_osc_clock() / 128) * INTERVAL_2MS_FLOAT;
	}

	// Enable Timer0 interrupt
    IRQ0EN |= IRQ_Timer0;

	T0CTL1 |= TIMER_ENABLE;

	SET_VECTOR(TIMER0, timer_isr);
}

int timer_interval_int(void)
{
	if(timer_state == TIMER_1MS) {
		return INTERVAL_1MS_INT;
	}
	else if(timer_state == TIMER_2MS) {
		return INTERVAL_2MS_INT;
	}
	else {
		return INTERVAL_4MS_INT;
	}
}

float timer_interval_float(void)
{
	if(timer_state == TIMER_1MS) {
		return INTERVAL_1MS_FLOAT;
	}
	else if(timer_state == TIMER_2MS) {
		return INTERVAL_2MS_FLOAT;
	}
	else {
		return INTERVAL_4MS_FLOAT;
	}
}