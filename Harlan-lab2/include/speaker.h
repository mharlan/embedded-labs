#ifndef SPEAKER_H

/*
	Initialize the speaker IO ports.

	Ground:PC0
	GPIO:PC1 (timer1 output)
 */
void init_speaker(void);

/*
	Play a note in a given octave for a given duration on the speaker.
 */
void play_note(int octave, unsigned char note[3], int duration, int bpm);

/*
 	Stop a note. This function is called by the duration timer.
 */
void stop_note(void);

/*
	Stop playing the ringtone.
 */
void stop_ringtone(void);

#endif