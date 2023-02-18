/*
 * notes.h
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */

#ifndef SHEET_MUSIC_H_
#define SHEET_MUSIC_H_

#include "music.h"

//taken from the imperial  march code and information and modified it
//modified to include sharp notes
//looking to generate a function that auto calculates these values
// for octives simple just bit shift the value

//for octive equation
// Notes * (1 << Octive_x)
// difference between notes are not consisist so i will just
// have to me the zero octive as a const value and use those for my code


// C1 - C0
//32.70 - 16.35 = 16.35

// C2 - C0
//65.41 - 16.35 = 49.06

// C2 - C1
//65.41 - 32.70 = 32.71

// C3 - C2
//130.81 - 65.41 = 65.4

	//scale BPM 120
	sTone SCALE[] =
	{
			//length  		octive 		note
			{ Whole_Note ,   Octave_5,   A	 },
			{ Whole_Note ,   Octave_5,   A_Sharp	 },
			{ Whole_Note ,   Octave_5,   B	 },
			{ Whole_Note ,   Octave_5,   C	 },
			{ Whole_Note ,   Octave_5,   C_Sharp	 },
			{ Whole_Note ,   Octave_5,   D	 },
			{ Whole_Note ,   Octave_5,   D_Sharp	 },
			{ Whole_Note ,   Octave_5,   E	 },
			{ Whole_Note ,   Octave_5,   F	 },
			{ Whole_Note ,   Octave_5,   F_Sharp	 },
			{ Whole_Note ,   Octave_5,   G	 },
			{ Whole_Note ,   Octave_5,   G_Sharp	 },
	};

	sTone A_Thousand_Years[] =
	{
			//length  		octive 		note
			//Phase 1
			{ Quarter_Note ,   Octave_3,   B_Flat	 },
			{ Eighth_Note ,   Octave_3,    B_Flat	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   B_Flat	 },
			{ Eighth_Note ,   Octave_3,    B_Flat	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   B_Flat	 },
			{ Eighth_Note ,   Octave_3,    B_Flat	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   A	 },
			{ Eighth_Note ,   Octave_3,    A },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   G	 },
			{ Eighth_Note ,   Octave_3,    G },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   G	 },
			{ Eighth_Note ,   Octave_3,    G },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   G	 },
			{ Eighth_Note ,   Octave_3,    G },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   F	 },
			{ Eighth_Note ,   Octave_3,    F },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   E	 },
			{ Eighth_Note ,   Octave_3,    E },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   E	 },
			{ Eighth_Note ,   Octave_3,    E },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Half_Note ,   Octave_3,      E	 },
			{ Quarter_Note ,   Octave_3,   E },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   B_Flat	 },
			{ Eighth_Note ,   Octave_3,    B_Flat	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_3,   B_Flat	 },
			{ Eighth_Note ,   Octave_3,    B_Flat	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Half_Note ,   Octave_3,  	   F	 },
			{ Quarter_Note ,   Octave_3,   F},

			//Verse 1
			//Hear beats fast colors and promises
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Eighth_Note ,   Octave_4,    G	 },
			{ Sixteenth_Note , Octave_4,   Rest	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Eighth_Note ,   Octave_4,    G	 },
			{ Sixteenth_Note , Octave_4,   Rest	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Eighth_Note ,   Octave_4,    G	 },
			{ Sixteenth_Note , Octave_4,   Rest	 },

			{ Sixteenth_Note ,   Octave_4,   B	 },
			{ Sixteenth_Note ,   Octave_4,   A	 },
			{ Eighth_Note ,   Octave_4,   	 A	 },
			{ Eighth_Note ,   Octave_4,      G	 },
			{ Quarter_Note ,   Octave_4,     G	 },
			{ Eighth_Note ,   Octave_4,      G	 },
			{ Sixteenth_Note , Octave_4,   	 Rest	 },
			{ Quarter_Note ,   Octave_4,   	 G	 },
			{ Eighth_Note ,   Octave_4,   	 G	 },
			{ Sixteenth_Note , Octave_4,   	 Rest	 },
			{ Quarter_Note ,   Octave_4,   	 G	 },
			{ Eighth_Note ,   Octave_4,   	 G	 },
			{ Sixteenth_Note , Octave_4,   	 Rest	 },

			//how to be brave?
			{ Eighth_Note ,   	 Octave_5,   D	 },
			{ Sixteenth_Note ,   Octave_5,   C	 },
			{ Sixteenth_Note ,    Octave_4,  B	 },
			{ Eighth_Note ,    Octave_4,   	 B	 },
			{ Sixteenth_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_4,   	 E	 },
			{ Eighth_Note ,   Octave_4,   	 E	 },

			//How can I love, when I'm afraid to fall
			{ Eighth_Note ,   	 Octave_5,   D	 },
			{ Sixteenth_Note ,   Octave_5,   C	 },
			{ Sixteenth_Note ,    Octave_4,  B	 },
			{ Eighth_Note ,    Octave_4,   	 B	 },
			{ Quarter_Note ,   	 Octave_4,   A	 },
			{ Eighth_Note ,    Octave_4,   	 B	 },
			{ Quarter_Note ,    Octave_4,    F_Sharp	 },
			{ Quarter_Note ,   Octave_4,   	 G	 },
			{ Eighth_Note ,   Octave_4,   	 G	 },
			{ Sixteenth_Note , Octave_4,     Rest	 },
			{ Quarter_Note ,   Octave_4,     G	 },
			{ Eighth_Note ,   Octave_4,      G	 },
			{ Sixteenth_Note , Octave_4,     Rest	 },
			{ Quarter_Note ,   Octave_4,     G	 },
			{ Sixteenth_Note ,   Octave_4,   Rest	 },

			// but watching you stand alone
			{ Sixteenth_Note ,   Octave_4,   G	 },
			{ Eighth_Note ,   Octave_4,   	 B	 },
			{ Eighth_Note ,   Octave_4,   	 A	 },
			{ Eighth_Note ,   Octave_4,   	 G	 },
			{ Quarter_Note ,   Octave_4,   	 G	 },
			{ Eighth_Note ,   Octave_4,   	 G	 },
			{ Sixteenth_Note , Octave_4,   	Rest	 },
			{ Eighth_Note ,   Octave_4,   	G	 },
			{ Quarter_Note ,   Octave_4,    G	 },
			{ Sixteenth_Note , Octave_4,   	Rest	 },
			{ Eighth_Note ,   Octave_4,   	G	 },
			{ Quarter_Note ,   Octave_4,   	G	 },
			{ Sixteenth_Note , Octave_4,    Rest	 },
			{ Eighth_Note ,   Octave_4,   	G	 },
			{ Quarter_Note ,   Octave_4,    G	 },

			//all of my doubt
			{ Eighth_Note ,   	 Octave_5,   D	 },
			{ Sixteenth_Note ,   Octave_5,   C	 },
			{ Sixteenth_Note ,    Octave_4,   B	 },
			{ Eighth_Note ,    Octave_4,   B	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Eighth_Note ,   Octave_4,   G	 },
			{ Sixteenth_Note , Octave_4,   Rest	 },
			{ Eighth_Note ,   Octave_4,   E	 },

			//suddenly goes away somehow
			{ Eighth_Note ,   	 Octave_5,   D	 },
			{ Sixteenth_Note ,   Octave_5,   C	 },
			{ Sixteenth_Note ,    Octave_4,  B	 },
			{ Eighth_Note ,    Octave_4,   	 B	 },
			{ Eighth_Note ,    Octave_4,   	 A	 },
			{ Sixteenth_Note ,    Octave_4,  B	 },
			{ Eighth_Note ,    Octave_4,     B	 },
			{ Sixteenth_Note ,    Octave_4,  F_Sharp	 },
			{ Quarter_Note ,   Octave_4,     G	 },
			{ Eighth_Note ,   Octave_4,      G	 },
			{ Sixteenth_Note , Octave_4,     Rest	 },
			{ Quarter_Note ,   Octave_4,     F_Sharp	 },


			//One step closer....
			{ Eighth_Note ,   	 Octave_5,   E	 },
			{ Sixteenth_Note ,   Octave_5,   E	 },
			{ Eighth_Note ,   	 Octave_5,   F_Sharp	 },
			{ Sixteenth_Note ,   Octave_5,   F_Sharp	 },
			{ Half_Note ,   	 Octave_5,   G	 },
			{ Quarter_Note ,   Octave_5,   	 G	 },
			{ Half_Note ,   	 Octave_5,   F_Sharp	 },
			{ Quarter_Note ,   Octave_5,   	 F_Sharp	 },

			//I have died everyday waiting for you
			{ Eighth_Note ,    Octave_4,   		 B	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 B	 },
			{ Eighth_Note ,    Octave_4,   	 	 B	 },
			{ Eighth_Note ,    Octave_4,   	 	 B	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 B	 },
			{ Eighth_Note ,    Octave_4,   	 	 B	 },
			{ Quarter_Note ,    Octave_5,   	 E	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 A	 },
			{ Quarter_Note ,    Octave_4,   	 G	 },


			//darling don't be afraid
			{ Eighth_Note ,    Octave_4,   		 B	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 B	 },
			{ Eighth_Note ,    Octave_4,   	 	 B	 },
			{ Eighth_Note ,    Octave_4,   	 	 B	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 B	 },
			{ Eighth_Note ,    Octave_4,   	 	 B	 },


			//I have loved you for a thousands year
			{ Quarter_Note ,    Octave_5,   	 E	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 A	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Sixteenth_Note , Octave_4,   Rest	 },
			{ Sixteenth_Note ,    Octave_4,   	 A	 },
			{ Quarter_Note ,    Octave_5,   	 C	 },
			{ Quarter_Note ,   Octave_4,   B	 },
			{ Eighth_Note ,   Octave_4,   	 E	 },
			{ Quarter_Note ,   Octave_4,   	 E	 },
			{ Eighth_Note ,   Octave_4,   	 E	 },
			{ Sixteenth_Note , Octave_4,   	Rest	 },
			{ Eighth_Note ,   Octave_4,   	E	 },
			{ Quarter_Note ,   Octave_4,    E	 },
			{ Sixteenth_Note , Octave_4,   	Rest	 },

			//Ill love you for a thousands more....
			{ Quarter_Note ,    Octave_5,   	 E	 },
			{ Sixteenth_Note ,    Octave_5,   	 D	 },
			{ Sixteenth_Note ,    Octave_4,   	 A	 },
			{ Quarter_Note ,    Octave_4,   	 G	 },
			{ Sixteenth_Note , Octave_4,   Rest	 },
			{ Sixteenth_Note ,    Octave_4,   	 A	 },
			{ Quarter_Note ,    Octave_5,   	 C	 },
			{ Quarter_Note ,   Octave_4,   B	 },
			{ Eighth_Note ,   Octave_4,   	 D	 },
			{ Quarter_Note ,   Octave_4,   	 D	 },
			{ Whole_Note ,   Octave_4,   	 D	 },
			{ Whole_Note , Octave_4,   	Rest	 },
			{ Whole_Note , Octave_4,   	Rest	 },

	};

	//BPM 160
	sTone Mario[]=
	{
			//length  			octive 		note

			//Intro
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			//{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			//{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Half_Note ,  	   Octave_5,   G	 },
			{ Eighth_Note ,    Octave_4,   G	 },

			//Phase 1
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_4,   E	 },
			{ Quarter_Note ,   Octave_4,   A	 },
			{ Eighth_Note ,    Octave_4,   B	 },
			{ Eighth_Note ,    Octave_4,   B_Flat	 },
			{ Quarter_Note ,    Octave_4,  A	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Quarter_Note ,   Octave_5,   A	 },
			{ Quarter_Note ,   Octave_5,   F	 },
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_5,   D	 },
			{ Quarter_Note ,   Octave_4,   B	 },

			//Phase 2
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_4,   E	 },
			{ Quarter_Note ,   Octave_4,   A	 },
			{ Eighth_Note ,    Octave_4,   B	 },
			{ Eighth_Note ,    Octave_4,   B_Flat	 },
			{ Quarter_Note ,    Octave_4,  A	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Quarter_Note ,   Octave_5,   A	 },
			{ Quarter_Note ,   Octave_5,   F	 },
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Quarter_Note ,   Octave_5,   E	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_5,   D	 },
			{ Quarter_Note ,   Octave_4,   B	 },

			//Phase 3
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Eighth_Note ,   Octave_5,   F_Sharp	 },
			{ Eighth_Note ,   Octave_5,   F	 },
			{ Quarter_Note ,   Octave_5,  D	 },
			{ Quarter_Note ,   Octave_5,  E	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_4,   A	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_4,   A	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_5,   D	 },
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Eighth_Note ,   Octave_5,   F_Sharp	 },
			{ Eighth_Note ,   Octave_5,   F	 },
			{ Quarter_Note ,   Octave_5,  D	 },
			{ Quarter_Note ,   Octave_5,  E	 },
			{ Quarter_Note ,   Octave_6,   C	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_6,   C	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },
			{ Quarter_Note ,   Octave_6,   C	 },
			{ Sixteenth_Note , Octave_5,   Rest	 },

			//ending
			{ Quarter_Note ,   Octave_5,   G	 },
			{ Eighth_Note ,   Octave_5,   F_Sharp	 },
			{ Eighth_Note ,   Octave_5,   F	 },
			{ Quarter_Note ,   Octave_5,  D	 },
			{ Quarter_Note ,   Octave_5,  E	 },
			{ Quarter_Note ,   Octave_4,   G	 },
			{ Quarter_Note ,   Octave_4,   A	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_4,   A	 },
			{ Quarter_Note ,   Octave_5,   C	 },
			{ Quarter_Note ,   Octave_5,   D	 },
			{ Quarter_Note ,   Octave_5,   D_Sharp	 },
			{ Quarter_Note ,   Octave_5,   D	 },
			{ Quarter_Note ,   Octave_5,   C	 },

			{ Whole_Note ,   Octave_5,   Rest	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
	};

	//BPM 80
	sTone ChristmasTree[]=
	{
			//length  			octive 		note

			//Intro
			{ Quarter_Note ,  	 Octave_5,   C	 },
			{ Eighth_Note ,  	 Octave_5,   F	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   F	 },
			{ Quarter_Note ,  	 Octave_5,   F	 },
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },

			//Phase 1
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Eighth_Note ,  	 Octave_5,   E	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   F	 },

			//Phase 2 same as Intro
			{ Quarter_Note ,  	 Octave_5,   C	 },
			{ Eighth_Note ,  	 Octave_5,   F	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   F	 },
			{ Quarter_Note ,  	 Octave_5,   F	 },
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },

			//Phase 3 same as Phase 1
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Eighth_Note ,  	 Octave_5,   E	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   F	 },

			//Phase 4
			{ Quarter_Note ,  	 Octave_6,   C	 },
			{ Eighth_Note ,  	 Octave_5,   C	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_6,   D	 },
			{ Quarter_Note ,  	 Octave_6,   C	 },
			{ Eighth_Note ,  	 Octave_6,   C	 },
			{ Sixteenth_Note ,   Octave_6,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   B_Flat	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Eighth_Note ,  	 Octave_5,   B_Flat	 },
			{ Sixteenth_Note ,   Octave_6,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_6,   C	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Sixteenth_Note ,   Octave_6,   Rest	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Sixteenth_Note ,   Octave_6,   Rest	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Sixteenth_Note ,   Octave_6,   Rest	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },

			//Ending
			{ Quarter_Note ,  	 Octave_5,   C	 },
			{ Eighth_Note ,  	 Octave_5,   F	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   F	 },
			{ Quarter_Note ,  	 Octave_5,   F	 },
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },

			//Phase 1
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   A	 },
			{ Quarter_Note ,  	 Octave_5,   B_Flat	 },
			{ Eighth_Note ,  	 Octave_5,   E	 },
			{ Sixteenth_Note ,   Octave_5,   Rest	 },
			{ Eighth_Note ,  	 Octave_5,   G	 },
			{ Quarter_Note ,  	 Octave_5,   F	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
			{ Whole_Note ,   Octave_5,   Rest	 },
	};


#endif /* SHEET_MUSIC_H_ */
