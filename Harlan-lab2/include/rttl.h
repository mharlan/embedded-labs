#ifndef RTTL_H
#define RTTL_H

/*
 	Plays the RTTL ringtone for a given
	RTTL ringtone ID.
 */
void play_rttl_ringtone(const char *ringtone);

/*
	Plays the next note of the loaded ringtone.
 */
void play_next_note(void);

#endif