Matthew Harlan
CSCI 4415
Lab 1

1. How many timers did you use for the LED display portion of the lab? Why?

I used one timer. I tried using two, but the second timer would never trigger. I then realized I could
keep track of larger intervals using a 2 ms timer by incrementing my own timers via incrementing floats.

2. Did you order the display characters by column or row? Does it matter?

I ordered it by row, but it doesn't matter for one character scrolling. If I had ordered everything by column it would have made
doing one column scrolling possible. I ordered it by row because matrix.h made this very easy.

3. Did you find that your display blinked or flickered, or that the characters seemed dim, or 
that one row or column of dots was brighter than the rest? If you solved that, what was 
the problem? If not, what do you think the problem is?

Yes. I solved it by speeding up the refresh rate of the LEDs. At 2 ms per row it looks very clean.

4. Did you use polling or interrupts to monitor the switch state? Why? 

I used polling because buttons PF6 and PF7 can't generate interrupts without connecting wires.

5. How did you de-bounce the switches?

I debounced the switches by sampling. When the state doesn't change after 40 ms I adjust the
button state.