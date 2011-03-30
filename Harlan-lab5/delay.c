
#include "delay.h"
#include "oscillator.h"

#include <zneo.h>

void delay_ms(int ms)
{
	PADD &= 0xFE;
    PAOUT |= 0x01;                  // take PA0 high;

    T2CTL0 = 0;                     // no settings
    T2CTL1 = 0x38;                  // disable, one shot
    T2HL=1;                         // initial value 
    T2R = get_osc_clock() / 128 / 1000 * ms;    // reload
    T2CTL1 |= 0x80;                 // start it
    while(T2CTL1 & 0x80) ;          // wait for it to be done

    PAOUT &= 0xFE;                  // take PA0 low
}
