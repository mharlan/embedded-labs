#include "speaker.h"
#include "timer.h"
#include "notes.h"
#include "timer.h"
#include "oscillator.h"

#include <zneo.h>
#include <string.h>
#include <ctype.h>

static int duration_timer;
static int duration_cutoff;

static void play_note(int octave, unsigned char note[3], int duration, int bpm);
static void stop_note(void);
static void stop_ringtone(void);
static void disable_speaker_timer(void);
static void init_speaker_timer(void);
static void start_speaker_timer(int frequency);
static int beats_to_duration(int beats, int bpm);

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
	Handles all speaker events.
 */
void speaker_events(void)
{
	if(duration_cutoff) {
		duration_timer += timer_interval_int();
		
		if(duration_timer >= duration_cutoff) {
			disable_speaker_timer();
		}
	}
}

/*
	Disables timer1 and sets PC1 low.
 */
void disable_speaker_timer(void)
{
	duration_cutoff = 0;
	duration_timer = 0;

	T1CTL1 |= TIMER_DISABLE;
	PCOUT &= ~0x02;	//set PC1 low
	PCAF &= ~0x02;
}

/*
	Play a note in a given octave for a given duration on the speaker.
 */
void play_note(int octave, unsigned char note[3], int duration, int bpm)
{
	//if not lowercase, make lowercase
	if(!islower(note[0])) {
		note[0] = tolower(note[0]);
	}

	//figure out what note it is
	if(!strncmp(note, "a", 2)) {
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_A]);
	}
	else if(!strncmp(note, "a#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_ASHARP]);
	}
	else if(!strncmp(note, "b", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_B]);
	}
	else if(!strncmp(note, "c", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_C]);
	}
	else if(!strncmp(note, "c#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_CSHARP]);
	}
	else if(!strncmp(note, "d", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_D]);
	}
	else if(!strncmp(note, "d#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_DSHARP]);
	}
	else if(!strncmp(note, "e", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_E]);
	}
	else if(!strncmp(note, "f", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_F]);
	}
	else if(!strncmp(note, "f#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_FSHARP]);
	}
	else if(!strncmp(note, "g", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_G]);
	}
	else if(!strncmp(note, "g#", 2))
	{
		start_speaker_timer(note_values[octave - NUM_OCTAVES][NOTE_GSHARP]);
	}

	//set timer for duration of note
	duration_timer = 0;
	duration_cutoff = beats_to_duration(duration, bpm);
}

/*
	Play a specific frequency note.

	This function can be used for testing speakers.
 */
void play_frequency(int frequency)
{
	start_speaker_timer(frequency);
}

/*
	Setup timer1.
 */
static void init_speaker_timer(void)
{
	T1CTL1 |= TIMER_DISABLE;

    T1CTL1 = TIMER_MODE_CONTINUOUS + TIMER_PRESCALE_64;
}

/*
 	Enable timer 1. The timer will go off every
	1 / (2 * frequency) seconds.
 */
static void start_speaker_timer(int frequency)
{
	float timeout;

	//calculate the timeout
	timeout = 1.0f / (float)frequency;

	// Initial counter value
    T1HL = 0x00;

	// Timer reload
    //   reload = clock / prescale * timeout  
    T1R = get_osc_clock() / 64 * timeout;

	// Enable Timer0 interrupt
    //IRQ1EN = IRQ_Timer1;

	T1CTL1 |= TIMER_ENABLE;

	//set PC1 as T1OUT
	PCAF |= 0x02;
}

/*
	Convert a duration to a time value using beats per minute.
 */
static int beats_to_duration(int beats, int bpm)
{
	return (int)((60.0f / (float)bpm) * (4.0f / (float)beats) * 1000.0f);
}

