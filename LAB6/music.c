/*
 * music.c
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */
#include "system.h"
#include "music.h"
#include <stdint.h>
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


static volatile TIMx* const TIM3 = (TIMx*) TIM3_BASE_ADDRESS;
static volatile uint32_t * const GPIO_B = (uint32_t*) GPIO_B_BASE_ADDRESS;
static volatile uint32_t* const NVIC_ISER = (uint32_t*)NVIC_BASE_ADDRESS;

unsigned int Half;
unsigned int Quarter;
unsigned int Eighth;
unsigned int Sixteenth;
unsigned int Whole;

static void gpio_init( void );
static uint32_t return_duration( eDurations time );
static float return_notevalue( eNotes note);
static void temp_setup( unsigned int BPM );
static void play_note( const sTone* tone);

static int tick_count_note_on = 0;
static sTone *(music_pointer);
static int BPM;
static int size;
static int play = 0;
static int current_count = 0;


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

int Music_status( void )
{
	return play;
}

void TIM3_init( void )
{
	gpio_init();
	delay_int();

	//to set the interrupt priority you will have to modify NVIC_IPR
	//This register provides an 8-bit field for each interrupt.
	//The location in which you should set the priority will be based on the
	//on the position value
	// EXAMPLE NVIC_IPR[29]
	// The processor only implements bits [7:4]
	// bits [3:0] reads as zeros
	// the lower the value the greater the priority of the interrupt

	//For this problem we will not have to implement any priority.

	//setting up the NVIC for the TIMER3
	//TIM3 IRQ_n = 29 position value Address 0x0000 00B4
	NVIC_ISER[0] = 1<<29;


	/*
	 * Notes:
	 * The auto-reload register is preloaded. The content of the preload
	 * register are transferred into the shadow register permanently
	 * or at each update event (UEV), depending on the auto-reload
	 * preload enable bit (ARPE) in TIMx_CR1 register.
	 *
	 * The counter is enabled by the pre scaler output CK_CNT which is only
	 *  enabled when the counter enabled bit is on
	 *
	 */
	//Setup of Timer
	// setting clock division to to 0
	// Auto-realed preload enabled for value
	//
	TIM3->CR1 &= ~(( 1 << 9) | (1 << 8) );
	TIM3->CR1 |=  ( 1 << 7); //Auto reload bit on auto files in the ARR

	//Counter is currently set up as an up counter
	// to run the counter simple set the CEN bit to high


	//looks like that slave mode control register and DMA/Interrupt register
	// will not be needed unless use an interrupt for Capture/Compare interrupt
	//set output mode to "toggle" on match in TIM3_CCMR1
	// we will have to modify the OC1M: Output compare mode we wll haave to
	// to select toggle which toggles OC1REF when TIM3_CNT = TIM3_CCR1
	// Therefore OC1M = 011
	TIM3->CCMR1 |=  ( ( 1 << 5 ) | (1 << 4) ); //Output compare mode 1 mode
	TIM3->DIER |= (1 << 0); //Enabled UI interrupt

	//disable the timer, for now
	TIM3->CR1 &= ~(1 << 0);

}

static void gpio_init( void )
{
	volatile uint32_t * const RCC = (uint32_t*) RCC_BASE_ADDRESS;
	RCC[RCC_AHB1ENR] |= (1 << 1); // Init the GPIO B RCC PIN
	RCC[RCC_APB1ENR] |= (1 << 1); // Init the TIM3 for RCC

	//setup the GPIO B as to alternate function mode for TIM3 for pin 4
	GPIO_B[MODER] |=  (1 << 9);
	GPIO_B[MODER] &= ~(1 << 8);

	//setup for Alternate function low registers
	// This is based on alternate function on STM32F11 figure 7
	// Time has the AF2 for AFRL for pins between 0-7
	/*
	 * AF0 -> system
	 * AF1 -> TIM1/2
	 * AF2 -> TIM3/4/5
	 * AF3 -> TIM9/10/11
	 *
	 * AFRLy selection for AF2 is 0010
	 * we will have to modify AFRL4
	 */

	GPIO_B[AFRL] |= (1 << 17);
}

static float return_notevalue( eNotes note)
{
	float note_value = 0.0;
	switch( note )
	{
		case Rest:
			note_value = 0;
			break;

		case A_Sharp: //same thing B_flat
			note_value = As;
			break;

		case B: //same for C flat
			note_value = B_;
			break;

		case C:  //same as B_sharp
			note_value = C_;
			break;

		case D_Flat: //same as C sharp
			note_value = Db;
			break;

		case D: //same as C sharp
			note_value = D_;
			break;

		case D_Sharp: //same E_flat
			note_value = Ds;
			break;

		case E:   //F_flat
			note_value = E_;
			break;

		case F: //E_sharp
			note_value = F_;
			break;

		case G_Flat: //same as F#
			note_value = Gb;
			break;

		case G:
			note_value = G_;
			break;

		case A_Flat: //same as G sharp
			note_value = Ab;
			break;

		case A:
			note_value = A_;
			break;
	}
	return note_value;
}

static void temp_setup( unsigned int BPM )
{
	Quarter = 60000/BPM;
	Half = 2 * Quarter;
	Whole = Quarter*4;
	Eighth =  Quarter/2;
	Sixteenth = Quarter/4;

}

static uint32_t return_duration( eDurations time )
{
	uint32_t return_val = 0;

	switch( time )
	{
	case Quarter_Note:
		return_val = Quarter;
		break;

	case Eighth_Note:
		return_val = Eighth;
		break;

	case Sixteenth_Note:
		return_val = Sixteenth;
		break;

	case Whole_Note:
		return_val = Whole;
		break;

	case Half_Note:
		return_val = Half;
		break;

	case None:
		return_val = 0;
		break;

	}

	return return_val;
}

static void play_note( const sTone* tone)
{

	float note_value = 0;
	eNotes struct_info = tone->eNote_Type;
	//calculated the notes raw value
	//get the needed value based on the note type and multiple by the octave
	note_value = return_notevalue(struct_info);

	uint32_t val = 0;
	uint32_t multi = 0;
	uint32_t ticks = 0;

	//in order to remove mis aligment issues  issues
	eOctives octive = tone->Octive_Type;

	multi = ( 1 << octive );
	val = (uint32_t) ( ( note_value )*(multi) );

	play = 1;

	//Set half-period count in the ARR  register
	if( val > 1)
	{
		ticks = (uint32_t) (CLK_SPEED/val )/2.0;
		float calculated_ticks = (CLK_SPEED/(float)ticks);

		TIM3->ARR = ticks;
		TIM3->CCR1 = ticks;
		//based on testing it looks like the lower the number the higher the
		//frequency

		//calculate the note speed being used for the delay
		//delay_ms( return_duration(tone->eLength_Type) );
		//calculate the number of ticks needed for the delay
		// this is done by the note type, ticks
		int delay_time = return_duration(tone->eLength_Type);

		tick_count_note_on = (calculated_ticks)*(delay_time/500);
		//enable the output of the timer
		// Enable output in TIM3_CCER
		TIM3->CCER |= 1; // CC1E = 1

	}
	else
	{
		//disable the output
		//disable the output in TIM3_CCER
		TIM3->CCER &= ~(1 << 0); // CC1E = 0

		//this means we have a rest for rest simply set the tick counter 500
		TIM3->ARR = 50;
		TIM3->CCR1 = 50;

		int delay_time = return_duration(tone->eLength_Type);
		tick_count_note_on = (delay_time/500)*50;
		//disable the output in TIM3_CCER
		TIM3->CCER &= ~(1 << 0); // CC1E = 0


	}

	TIM3->CR1 |= 1; //enable the counter of TIM
}

int Console_show(int song_selection)
{
	int set = 1;
	switch( song_selection)
	{
	case 1:
		//a pointer to an array of structures? What should I do with this?
		music_pointer = (sTone*) SCALE;
		BPM = 120;
		size = (sizeof(SCALE)/3);
		break;
	case 2:
		//a pointer to an array of structures? What should I do with this?
		music_pointer = (sTone*) Mario;
		BPM = 120;
		size = (sizeof(Mario)/3);
		break;
	case 3:
		//a pointer to an array of structures? What should I do with this?
		music_pointer = (sTone*) A_Thousand_Years;
		BPM = 80;
		size = (sizeof(A_Thousand_Years)/3);
		break;
	case 4:
		//a pointer to an array of structures? What should I do with this?
		music_pointer = (sTone*) ChristmasTree;
		BPM = 100;
		size = (sizeof(ChristmasTree)/3);
		break;
	default:
		printf("Error User has picked a song that does not exist\n"
				"plz try again\n");
		set = 0;
		BPM = 1;
	}


	temp_setup(BPM);
	TIM3->DIER |= (1 << 0); //Enabled UI interrupt

	if( set )
	{
		//play the first note
		play_note( music_pointer );

	}
	return set;
}

void TIM3_IRQHandler( void )
{


	//clear the TIE Update interrupt flag
	TIM3->SR &= ~(1 << 0);

	//decrease the value
	tick_count_note_on--;

	//once the timer counter expires turn the note off and then move to the
	// the next next should be imported imported
	if( tick_count_note_on <=0 )
	{

		//move to the next note
		tick_count_note_on = 0;
		music_pointer++;
		if( current_count < (size - 1) )
		{
			play_note( music_pointer );
			current_count++;
			play = 1;
		}
		else
		{
			BPM = 0;
			size = 0;
			//we have finished playing music
			play = 0;
			current_count = 0;
			//turn the output pin off
			TIM3->CCER &= ~(1 << 0); // CC1E = 0
			TIM3->DIER &= ~(1 << 0); //disable the UI interrupt
		}
	}
}


