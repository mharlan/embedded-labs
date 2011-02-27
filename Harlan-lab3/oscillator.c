#include "oscillator.h"

#include <zneo.h>

static int osc_clock;

#define CLOCK_5_52MHZ   5520000
#define CLOCK_18_432MHZ 18432000

/*
	Unlocks the oscillator control register and selects either
	the 5.5 or 18.43 mHz oscillator.

	OSC_5_52MHZ or OSC_18_432MHZ
 */
void init_oscillator(int osc)
{
	// unlock the oscillator control register
	OSCCTL = 0xE7; OSCCTL = 0x18;  
   
	if(osc == OSC_18_432MHZ) {                 
		// 61 = 0110_0001 = external 18.432 Hz
		OSCCTL = 0x61;
		osc_clock = CLOCK_18_432MHZ;
	}
	//default oscillator setting
	else {
		// A0 = 1010_0000 = internal 5.52 MHz
		OSCCTL = 0xA0;
		osc_clock = CLOCK_5_52MHZ;
	}
}

/*
 	Return the current oscillator clockspeed in Hz.
 */
int get_osc_clock(void)
{
	return osc_clock;
}

void oscillator_settings_display(void)
{
	
}
