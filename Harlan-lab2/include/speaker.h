#ifndef SPEAKER_H

/*
	Initialize the speaker IO ports.

	Ground:PC0
	GPIO:PC1 (timer1 output)
 */
void init_speaker(void);

/*
	Handles all speaker events.
 */
void speaker_events(void);

/*
	Disables timer1 and sets PC1 low.
 */
void disable_speaker_timer(void);

/*
	Play a note in a given octave for a given duration on the speaker.
 */
void play_note(int octave, unsigned char note[3], int duration, int bpm);

/*
	Play a specific frequency note.

	This function can be used for testing speakers.
 */
void play_frequency(int frequency);

#endif