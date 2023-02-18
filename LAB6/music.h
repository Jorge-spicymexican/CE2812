/*
 * music.h
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#define CLK_SPEED 16000000L //clock speed being used

//notes pre processors s:sharp b:flat
#define	C_ 16.35
#define	Bs 16.35
#define	Cs	17.32
#define	Db	17.32
#define	D_	18.35
#define	Eb	19.45
#define	Ds	19.45
#define	E_	20.60
#define	Fb	20.60
#define	F_	21.83
#define	Es	21.83
#define	Fs	23.12
#define	Gb	23.12
#define	G_	24.50
#define	Ab	25.96
#define	Gs	25.96
#define	A_	27.50
#define	As	29.14
#define	Bb	29.14
#define	B_	30.87
#define Cb  30.87


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



//type of notes that exist on an octive piano
typedef enum
{
	Rest    = 0,

	A_Sharp = 1, //same as B_flat
	B_Flat  = 1,

	B		= 2,
	C_Flat  = 2,

	B_Sharp = 3, //same as C
	C		= 3,

	C_Sharp = 4, //same D_flat
	D_Flat  = 4,

	D       = 5,

	D_Sharp = 6, //same as E_flat
	E_Flat  = 6,

	E       = 7, //same as F_flat
	F_Flat  = 7,

	E_Sharp = 8, //same as F_sharp
	F		= 8,

	F_Sharp = 9, //same as G_flat
	G_Flat  = 9,

	G       = 10,

	G_Sharp = 11, //same as A_flat
	A_Flat  = 11,

	A 		= 12,



} eNotes;


typedef enum
{
	Octave_0 = 0,
	Octave_1 = 1,
	Octave_2 = 2,
	Octave_3 = 3,
	Octave_4 = 4,
	Octave_5 = 5,
	Octave_6 = 6,
	Octave_7 = 7,
	Octave_8 = 8,

} eOctives;

typedef enum
{
	Quarter_Note = 1,
	Eighth_Note = 2,
	Sixteenth_Note = 3,
	Whole_Note = 4,
	Half_Note = 5,
	None = 0,

} eDurations;


typedef struct
{
	eDurations eLength_Type;
	eOctives Octive_Type;
	eNotes eNote_Type;

} sTone;


//time variables
extern unsigned int Half;
extern unsigned int Quarter;
extern unsigned int Eighth;
extern unsigned int Sixteenth;
extern unsigned int Whole;
extern unsigned int uiBPM; //speed of the sheet music this will be the first
						//variable to be given
void TIM3_init( void );
int Console_show(int song_selection);
int Music_status( void );

#endif /* MUSIC_H_ */
