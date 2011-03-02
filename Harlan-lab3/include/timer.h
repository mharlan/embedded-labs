#ifndef __TIMER_H
#define __TIMER_H

// Timer enable and disable
#define TIMER_DISABLE 0x00
#define TIMER_ENABLE  0x80

// Timer modes
#define TIMER_MODE_ONESHOT        0x00
#define TIMER_MODE_CONTINUOUS     0x01
#define TIMER_MODE_COUNTER        0x02
#define TIMER_MODE_PWM            0x03
#define TIMER_MODE_CAPTURE        0x04
#define TIMER_MODE_COMPARE        0x05
#define TIMER_MODE_GATED          0x06
#define TIMER_MODE_CAPTURECOMPARE 0x07

// Timer prescale values
#define TIMER_PRESCALE_1   0x00
#define TIMER_PRESCALE_2   0x08
#define TIMER_PRESCALE_4   0x10
#define TIMER_PRESCALE_5   0x18
#define TIMER_PRESCALE_16  0x20
#define TIMER_PRESCALE_32  0x28
#define TIMER_PRESCALE_64  0x30
#define TIMER_PRESCALE_128 0x38

// Timer output pin polarity
#define TIMER_TPOL_1 0x40
#define TIMER_TPOL_0 0x00

// Timer Interupt Configuration
#define TIMER_TICONFIG_RELOAD   0x00
#define TIMER_TICONFIG_DISABLED 0x40

// Timer cascade
#define TIMER_CASCADE     0x10
#define TIMER_CASCADE_NOT 0x00

// Timer PWM delay
#define TIMER_PWM_DELAY_0  0x00
#define TIMER_PWM_DELAY_2  0x02
#define TIMER_PWM_DELAY_4  0x04
#define TIMER_PWM_DELAY_8  0x06
#define TIMER_PWM_DELAY_16 0x08

// Timer capture mode
#define TIMER_INPUT_CAPTURE_OFF 0x00
#define TIMER_INPUT_CAPTURE_ON  0x01

#define TIMER_1MS 1
#define TIMER_2MS 2
#define TIMER_4MS 4

// These are IRQ0 register bits. I didn't define
// All 3 IRQ registers or all 24 bits. 
#define IRQ_Timer0 0x20
#define IRQ_Timer1 0x40
#define IRQ_Timer2 0x80

/*
	Initialize and start the global timer (timer0).

	TIMER_1MS, TIMER_2MS, TIMER_4MS
 */
extern void init_timer(int mode);

/*
	The timer interval as an int, in ms.
 */
extern int timer_interval_int(void);

/*
 	The timer interval as a float, 1.0 is a second.
 */
extern float timer_interval_float(void);

/*
	Print the current configuration for timers 0 through 2.
 */
extern void timers_print_config(const char *value);

#endif