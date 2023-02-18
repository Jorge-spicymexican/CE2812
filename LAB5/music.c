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

unsigned int Half;
unsigned int Quarter;
unsigned int Eighth;
unsigned int Sixteenth;
unsigned int Whole;

static void gpio_init( void );
static uint32_t return_duration( eDurations time );
static float return_notevalue( eNotes note);

void TIM3_init( void )
{
	gpio_init();
	delay_int();
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
	TIM3->CCMR1 |=  ( ( 1 << 5 ) | (1 << 4) );

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

void temp_setup( unsigned int BPM )
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


void play_music(sTone* musicpointer, int length)
{

	for(int i = 0; i < length ; i++)
	{
		play_note( musicpointer );
		musicpointer++;
	}
}




void play_note( const sTone* tone)
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


	//Set half-period count in the ARR  register
	if( val > 1)
	{
		ticks = (uint32_t) (CLK_SPEED/val )/2.0;
		TIM3->ARR = ticks;
		TIM3->CCR1 = ticks;
		//basically the CCR1 will count down/or overflows and once it reaches CNT
		//it should toggle the output pin when the CCR1 has expired
		//to gets reloaded by the ARR register. (I think)
		// Enable output in TIM3_CCER
		TIM3->CCER |= 1; // CC1E = 1


		TIM3->CR1 |= 1; //enable the counter of TIM

		//based on testing it looks like the lower the number the higher the
		//frequency

		//calculate the note speed being used for the delay
		delay_ms( return_duration(tone->eLength_Type) );

		//disable the output in TIM3_CCER
		TIM3->CCER &= ~(1 << 0); // CC1E = 0
		TIM3->CR1 &= ~1; //disable the counter of TIM
	}
	else
	{
		//disable the output in TIM3_CCER
		TIM3->CCER &= ~(1 << 0); // CC1E = 0
		TIM3->CR1 &= ~1; //disable the counter of TIM
		//calculate the note speed being used for the delay
		delay_ms( return_duration(tone->eLength_Type) );
	}

}

/* did not work for my implementation will have to this some over time :( */
void read_sheet(char* filename)
{

	char ErrorCode = 0;
	FILE* ptr;
	char str[255];

	ptr = fopen(filename, "r");
	if( ptr == NULL)
	{
		ErrorCode = 1; //file could not be opened
		printf("Error file could not be found");
	}
	else
	{
		while( fgets(str, 255, ptr) !=NULL)
		{
			printf("%s", str);
		}
	}
}
