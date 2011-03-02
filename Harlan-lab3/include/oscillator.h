#ifndef __OSCILLATOR_H
#define __OSCILLATOR_H

#define OSC_5_52MHZ   1
#define OSC_18_432MHZ 2

/*
	Unlocks the oscillator control register and selects either
	the 5.5 or 18.43 mHz oscillator.

	OSC_5_52MHZ or OSC_18_432MHZ
 */
extern void init_oscillator(int osc);

/*
 	Return the current oscillator clockspeed in Hz.
 */
extern int get_osc_clock(void);

/*
	Print the current oscillator configuration.
 */
extern void osc_print_config(void);

#endif