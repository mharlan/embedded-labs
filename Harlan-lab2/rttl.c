#include "rttl.h"
#include "speaker.h"

#include <zneo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOTES 100

struct rttl_note {
	int   octave;
	char  note[3];
	float duration;
};

static struct rttl_note song[MAX_NOTES];
static unsigned int num_notes = 0;
static unsigned int song_pos = 0;

static void parse_rttl_ringtone(const char *ringtone);
static float beats_to_duration(int beats, int bpm);

/*
 	Plays the RTTL ringtone for a given
	RTTL ringtone ID.
 */
void play_rttl_ringtone(const char *ringtone)
{
	parse_rttl_ringtone(ringtone);
	play_next_note();
}

/*
	Plays the next note of the loaded ringtone.
 */
void play_next_note(void)
{
	if(num_notes > 0) {
		play_note(song[song_pos].octave, song[song_pos].note, song[song_pos].duration);
		
		song_pos = (song_pos + 1) % num_notes;
	}	
}

/*
	Parse the RTTL ringtone into memory to be played on the speaker.
 */
static void parse_rttl_ringtone(const char *ringtone)
{
	unsigned char *rttl_song;
	unsigned char *token;
	unsigned char number_token[4];
	unsigned char test;

	size_t token_length;

	int octave;
	int duration;
	int bpm;
	int notes;
	int token_pos;

	num_notes = 0;
	song_pos = 0;

	token_length = strlen(ringtone) + 1;
	rttl_song = malloc(sizeof(*rttl_song) * token_length);
	if(rttl_song == NULL) {
		return;
	}
	strcpy(rttl_song, ringtone);

	//grab the name
	token = strtok(rttl_song, ":,");
	if(token != NULL) {
		//set name of song to LED
	}

	//default note duration, d=Value
	token = strtok(NULL, ":,");
	if(token != NULL) {
		if(token[0] == 'd') {
			duration = atoi(&token[2]);
		}
		//incorrect rttl syntax, return
		else {
			return;
		}
	}
	//incorrect rttl syntax, return
	else {
		return;
	}

	//default octave, o=Value
	token = strtok(NULL, ":,");
	if(token != NULL) {
		if(token[0] == 'o') {
			octave = atoi(&token[2]);
		}
		//incorrect rttl syntax, return
		else {
			return;
		}
	}
	//incorrect rttl syntax, return
	else {
		return;
	}	
	
	//default bpm, b=Value
	token = strtok(NULL, ":,");
	if(token != NULL) {
		if(token[0] == 'b') {
			bpm = atoi(&token[2]);
		}
		//incorrect rttl, return syntax
		else {
			return;
		}
	}
	//incorrect rttl syntax, return
	else {
		return;
	}

	//grab each note
	notes = 0;
	while((token = strtok(NULL, ":,")) != NULL) {
		token_length = strlen(token);
		token_pos = 0;

		//get the size of the duration
		while(isdigit(token[token_pos])) {
			token_pos++;

			//incorrect rttl, return syntax
			if(token_pos >= token_length) {
				return;
			}
		}

		//if more than 2 digits for duration
		//incorrect rttl syntax, return
		if(token_pos > 2) {
			return;
		}

		//has a duration specified
		if(token_pos != 0) {
			memcpy(number_token, token, token_pos);
			number_token[token_pos] = '\0';

			song[notes].duration = beats_to_duration(atoi(number_token), bpm);
		}
		//use default duration
		else {
			song[notes].duration = beats_to_duration(duration, bpm);
		}

		//if more than one character left
		if((token_length - token_pos) > 1) {
			//note is note sharp
			if(isdigit(token[token_pos + 1])) {
				song[notes].note[0] = token[token_pos];
				song[notes].note[1] = '\0';
				token_pos++;
			}
			//note is sharp
			else {
				memcpy(song[notes].note, &token[token_pos], 2);
				song[notes].note[2] = '\0';
				token_pos += 2;
			}

			//octave is specifed
			if(token_pos < token_length && isdigit(token[token_pos])) {
				song[notes].octave = atoi(&token[token_pos]);
			}
			//otherwise use default
			else {
				song[notes].octave = octave;
			}
		}
		//just a non sharp note, use default octave
		else {
			song[notes].note[0] = token[token_pos];
			song[notes].note[1] = '\0';
			song[notes].octave = octave;
		}

		if((notes + 1) < MAX_NOTES) {
			notes++;
		}
		else {
			break;
		}
	}

	//pad with a rest to repeat
	if((notes + 1) < MAX_NOTES) {
		song[notes].note[0] = 'P';
		song[notes].note[1] = '\0';
		song[notes].duration = beats_to_duration(1, bpm);
		notes++;
	}

	num_notes = notes;
	free(rttl_song);
}

/*
	Convert a duration to a time value using beats per minute.
 */
static float beats_to_duration(int beats, int bpm)
{
	return (60.0f / (float)bpm) * (4.0f / (float)beats);
}