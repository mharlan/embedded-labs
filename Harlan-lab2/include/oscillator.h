#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#define OSC_5_52MHZ   1
#define OSC_18_432MHZ 2

/*
	Unlocks the oscillator control register and selects either
	the 5.5 or 18.43 mHz oscillator.

	OSC_5_52MHZ or OSC_18_432MHZ
 */
void init_oscillator(int osc);

/*
 	Return the current oscillator clockspeed in Hz.
 */
int get_osc_clock(void);

#endif