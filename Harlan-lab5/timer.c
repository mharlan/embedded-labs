#include "timer.h"
#include "oscillator.h"
#include "LED.h"
#include "buttons.h"
#include "uart.h"

#include <zneo.h>
#include <string.h>

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

void timers_print_config(const char *value)
{
	uart_printf("\n");
	if(strcmp(value, "0") == 0) {
		uart_printf("T0H:\t%.2X\n", T0H);
		uart_printf("T0L:\t%.2X\n", T0L);
		uart_printf("T0RH:\t%.2X\n", T0RH);
		uart_printf("T0RL:\t%.2X\n", T0RL);
		uart_printf("T0PWMH:\t%.2X\n", T0PWMH);
		uart_printf("T0PWML:\t%.2X\n", T0PWML);
		uart_printf("T0CTL0:\t%.2X\n", T0CTL0);
		uart_printf("T0CTL1:\t%.2X\n", T0CTL1);
	}
	else if(strcmp(value, "1") == 0) {
		uart_printf("T1H:\t%.2X\n", T1H);
		uart_printf("T1L:\t%.2X\n", T1L);
		uart_printf("T1RH:\t%.2X\n", T1RH);
		uart_printf("T1RL:\t%.2X\n", T1RL);
		uart_printf("T1PWMH:\t%.2X\n", T1PWMH);
		uart_printf("T1PWML:\t%.2X\n", T1PWML);
		uart_printf("T1CTL0:\t%.2X\n", T1CTL0);
		uart_printf("T1CTL1:\t%.2X\n", T1CTL1);
	}
	else if(strcmp(value, "2") == 0) {
		uart_printf("T2H:\t%.2X\n", T2H);
		uart_printf("T2L:\t%.2X\n", T2L);
		uart_printf("T2RH:\t%.2X\n", T2RH);
		uart_printf("T2RL:\t%.2X\n", T2RL);
		uart_printf("T2PWMH:\t%.2X\n", T2PWMH);
		uart_printf("T2PWML:\t%.2X\n", T2PWML);
		uart_printf("T2CTL0:\t%.2X\n", T2CTL0);
		uart_printf("T2CTL1:\t%.2X\n", T2CTL1);
	}
	else {
		uart_printf("Select a timer 0-2.\n");
	}
}
