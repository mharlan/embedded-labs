#ifndef NOTES_H
#define NOTES_H

#define NUM_OCTAVES 4
#define NUM_NOTES   12

#define NOTE_A      10
#define NOTE_ASHARP 11
#define NOTE_B      12
#define NOTE_C      1
#define NOTE_CSHARP 2
#define NOTE_D      3
#define NOTE_DSHARP 4
#define NOTE_E      5
#define NOTE_F      6
#define NOTE_FSHARP 7
#define NOTE_G      8
#define NOTE_GSHARP 9

/*
	Note values for octaves 4-7 as index 0-3 in the array.
 */
unsigned int note_values[NUM_OCTAVES][NUM_NOTES] = 
{
	//octave 4
	{262,	//C
	 277,	//C#
	 294,	//D
	 311,	//D#
	 330,	//E
	 349,	//F
	 370,	//F#
	 392,	//G
	 415,	//G#
	 440,	//A
	 466,	//A#
	 494},	//B

	//octave 5
	{523,
	 554,
	 587,
	 622,
	 659,
	 698,
	 740,
	 784,
	 831,
 	 880,
	 932,
	 988},

	//octave 6
	{1047,
	 1109,
	 1175,
	 1245,
	 1319,
	 1397,
	 1480,
	 1568,
	 1661,
	 1760,
	 1865,
	 1976},

	//octave 7
	{2093,
	 2217,
	 2349,
	 2489,
	 2637,
	 2794,
	 2960,
	 3136,
	 3322,
	 3520,
	 3729,
	 3951},
};

#endif