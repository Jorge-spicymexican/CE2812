/*
 * measure.c
 *
 *  Created on: Jan 31, 2023
 *      Author: jurado-garciaj
 */

#include "system.h"
#include <stdint.h>
#include "measure.h"
#include "limits.h"


//file scope functions
static void gpio_init( void );
static void Clear_Buffers( void );
static void Get_Min_and_Max( void );

//file scope variables
static volatile TIMx* const TIM2 = (TIMx*) TIM2_BASE_ADDRESS;
static volatile uint32_t * const GPIO_A = (uint32_t*) GPIO_A_BASE_ADDRESS;
static volatile uint32_t* const NVIC_ISER = (uint32_t*) NVIC_BASE_ADDRESS;
static volatile sDatalog Log;

int ISR_DONE( void )
{
	//printf("Collection value %d\n", Log.Collection_Done);

	if( Log.Collection_Done )
	{
		Log.Collection_Done = FALSE;
		return TRUE;
	}
	return FALSE;
}

int Get_MinSample( void )
{
	return 	Log.min_sample;
}


int Get_MaxSample( void )
{
	return 	Log.max_sample;
}


float Calculate_FREQZ( void)
{
	uint32_t i=0;
	float sum = 0;
	for(i=0;i < DELTA_COUNT; i++)
	{
		Log.Delta_DATA[i] = Log.Raw_DATA[i+1] - Log.Raw_DATA[i];
		sum +=(float)Log.Delta_DATA[i];
	}

	Get_Min_and_Max();
	//average out the delta array and return frequency
	Log.measuredFreqz = ( (F_CPU) / ( (float)(sum/DELTA_COUNT) ) );

	return Log.measuredFreqz;
}

void Clear_Log( void )
{
	//clear data buffers
	Clear_Buffers();
	Log.Collection_Done = FALSE;
	Log.max_sample = 0;
	Log.measuredFreqz = 0.0;
	Log.min_sample = 0;
}
static void Get_Min_and_Max( void )
{
	int min=UINT_MAX;
	int max=0;
	int i=0;

	for(i=0;i<DELTA_COUNT; i++)
	{
		//check for min value
		if(Log.Delta_DATA[i] < min)
		{
			min = Log.Delta_DATA[i];
		}

		//check if its greater
		if(Log.Delta_DATA[i] > max)
		{
			max = Log.Delta_DATA[i];
		}
	}

	Log.min_sample = min;
	Log.max_sample = max;

}


static void Clear_Buffers( void )
{
	int i=0;
	for(i=0;i < DELTA_COUNT; i++)
	{
		Log.Delta_DATA[i] = 0;
	}

	for(i=0;i < RAW_COUNT; i++)
	{
		Log.Raw_DATA[i] = 0;
	}

}


void START_TIM2( void)
{
	TIM2->DIER |= (1 << 1); //capture/Compare 1 interrupt disabled
}


//init the tim2 to input capture mode
void TIM2_init( void )
{
	gpio_init();

	//to set the interrupt priority you will have to modify NVIC_IPR
	//This register provides an 8-bit field for each interrupt.
	//The location in which you should set the priority will be based on the
	//on the position value
	// EXAMPLE NVIC_IPR[29]
	// The processor only implements bits [7:4]
	// bits [3:0] reads as zeros
	// the lower the value the greater the priority of the interrupt

	//For this problem we will not have to implement any priority.

	// TIMER 2 INTERRUPT SETUP
	// POS  PRI TYPE-PRI  Name address location
	// 28 	35 	settable TIM2  0x0000 00B0
	//setting up the NVIC for the TIMER3
	//TIM2 IRQ_n = 28 position value Address 0x0000 00B0
	NVIC_ISER[0] = 1<<28;


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
	TIM2->CR1 &= ~(( 1 << 9) | (1 << 8) );
	TIM2->CR1 |=  ( 1 << 7); //Auto reload bit on auto files in the ARR
	//disable the timer, for now
	TIM2->CR1 &= ~(1 << 0);
	//Counter is currently set up as an up counter
	// to run the counter simple set the CEN bit to high
	TIM2->ARR = (uint32_t)UINT_MAX;
	TIM2->CCER &= ~(1<<0); //seting the timer off for writing below registers
	//Capture/compare mode register is broken down into 2 sets
	//Output compare mode and input compare mode
	//CCxs bit defines weather it is capture or compare mode.
	TIM2->CCMR1 |= ~(1<<1);
	TIM2->CCMR1 |= (1<<0);
	TIM2->CCMR1 |= ( (F_SAMPLING_PER32_N8)<<4); //filter
	TIM2->CCMR1 &= ~( (1<<2)|(1<<3) ); //Setting the prescalar to zero
	TIM2->CCER &= ~(1<<1); //set to noninverted/rising edge
	TIM2->CCER |= (1<<0); //Settting it to active again
	TIM2->DIER &= ~(1 << 1); //capture/Compare 1 interrupt disabled
	TIM2->DIER = 0; //make sure everything is disabled
	//enable the timer
	TIM2->CR1 |= (1 << 0);

}


static void gpio_init( void )
{
	volatile uint32_t * const RCC = (uint32_t*) RCC_BASE_ADDRESS;
	RCC[RCC_AHB1ENR] |= (1 << 0); // Init the GPIO A RCC PIN
	RCC[RCC_APB1ENR] |= (1 << 0); // Init the TIM2 for RCC

	//setup the GPIO A as to alternate function mode for TIM2 for pin 15
	GPIO_A[MODER] |=  (1 << 31); //PA15
	GPIO_A[MODER] &= ~(1 << 30); //PA15

	//setup for Alternate function low registers
	// This is based on alternate function on STM32F11 figure 7
	// Time has the AFRL2 for AFRL for pins between 0-7
	/*
	 * AF0 -> system
	 * AF1 -> TIM1/2
	 * AF2 -> TIM3/4/5
	 * AF3 -> TIM9/10/11
	 *
	 * AFRLy selection for AF1 is 0x0001
	 * we will have to modify AFRH15
	 */

	GPIO_A[AFRH] |= (1 << 28);
	GPIO_A[PUPDR] |= (1 << 30);
}


void TIM2_IRQHandler( void )
{
	static int counter = 0;
	//clear the CCMR1 interrupt flag
	//I am lazy we are just clearing all of the flags at this point
	TIM2->SR = 0;

	//save value into the delta flag
	Log.Raw_DATA[counter] = (uint32_t)TIM2->CNT;

	counter++;

	if( counter >= RAW_COUNT)
	{
		Log.Collection_Done = TRUE;
		counter=0;
		TIM2->DIER &= ~(1 << 1); //capture/Compare 1 interrupt disabled
	}
}

