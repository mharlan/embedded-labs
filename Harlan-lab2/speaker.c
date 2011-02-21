#include "speaker.h"
#include "timer.h"
#include "notes.h"

#include <zneo.h>
#include <string.h>
#include <ctype.h>

static void disable_speaker_timer(void);
static void init_speaker_timer(void);
static void start_speaker_timer(unsigned int frequency);

float duration_timer;
float duration_cutoff;

/*
	Initialize the speaker IO ports.

	Ground:PC0
	GPIO:PC1 (timer1 output)
 */
void init_speaker(void)
{
	PCDD &= ~0x03;	//set PC0 and PC1 as outputs
	PCOUT &= ~0x03; //set PC0 and PC1 low

	duration_timer = 0;
	duration_cutoff = 0;

	init_speaker_timer();
}

/*
	Play a note in a given octave for a given duration on the speaker.
 */
void play_note(int octave, unsigned char note[3], float duration)
{
	//if not lowercase, make lowercase
	if(!islower(note[0])) {
		note[0] = tolower(note[0]);
	}

	//figure out what note it is
	if(!strncmp(note, "a", 2)) {
		start_speaker_timer(note_values[octave - NUM_OCTAVES][0]);
	}
	else if(!strncmp(note, "a#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][1]);
	}
	else if(!strncmp(note, "b", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][2]);
	}
	else if(!strncmp(note, "c", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][3]);
	}
	else if(!strncmp(note, "c#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][4]);
	}
	else if(!strncmp(note, "d", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][5]);
	}
	else if(!strncmp(note, "d#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][6]);
	}
	else if(!strncmp(note, "e", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][7]);
	}
	else if(!strncmp(note, "f", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][8]);
	}
	else if(!strncmp(note, "f#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][9]);
	}
	else if(!strncmp(note, "g", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][10]);
	}
	else if(!strncmp(note, "g#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][11]);
	}

	//set timer for duration of note
	duration_timer = 0;
	duration_cutoff = duration;
}

/*
 	Stop a note. This function is called by the duration timer.
 */
void stop_note(void)
{
	disable_speaker_timer();
}

/*
	Stop playing the ringtone.
 */
void stop_ringtone(void)
{
	duration_cutoff = 0;
	duration_timer = 0;

	disable_speaker_timer();
}

/*
	Disables timer1 and sets PC1 low.
 */
static void disable_speaker_timer(void)
{
	T1CTL1 |= TIMER_DISABLE;
	PCOUT &= ~0x02;	//set PC1 low
	PCAF &= ~0x02;
}

/*
	Setup timer1.
 */
static void init_speaker_timer(void)
{
	T1CTL1 |= TIMER_DISABLE;

    T1CTL1 = TIMER_MODE_CONTINUOUS + TIMER_PRESCALE_64;

    // Initial counter value
    T1HL = 0x00;
}

/*
 	Enable timer 1. The timer will go off every
	1 / (2 * frequency) seconds.
 */
static void start_speaker_timer(unsigned int frequency)
{
	float timeout;

	//calculate the timeout
	timeout = 1.0f / (2.0f * (float)frequency);

	// Initial counter value
    T1HL = 0x00;

	// Timer reload
    //   reload = clock / prescale * timeout  
    T1R = CLOCK / 64 * timeout;

	// Enable Timer0 interrupt
    IRQ1EN = IRQ_Timer1;

	T1CTL1 |= TIMER_ENABLE;

	//set PC1 as T1OUT
	PCAF |= 0x02;
}
