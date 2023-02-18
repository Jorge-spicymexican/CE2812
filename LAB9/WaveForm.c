/*
 * WaveForm.c
 *
 *  Created on: Feb 1, 2023
 *      Author: jurado-garciaj
 */

#include "system.h"
#include <stdint.h>
#include "waveform.h"
#include "limits.h"
#include "stdlib.h"
#include "stdio.h"

//static function prototypes
static void GPIO_init( void );
static void Reset_Wave( void );
static void TIMER_init( void );

//file scope variables
static volatile ADCx* const ADC12 = (ADCx*) ADC1_BASE_ADDRESS;
static volatile TIMx* const TIM4 = (TIMx*) TIM4_BASE_ADDRESS;
static volatile uint32_t * const GPIO_B = (uint32_t*) GPIO_B_BASE_ADDRESS;
static volatile uint32_t* const NVIC_ISER = (uint32_t*) NVIC_BASE_ADDRESS;
static volatile uint32_t * const RCC = (uint32_t*) RCC_BASE_ADDRESS;
static volatile sWaveform Wave;

//Init the adc for single conversion
void ADC12_IN9_init( void )
{
	GPIO_init();

	TIMER_init();

	//turn on ADC (can be deferred before reading)
	ADC12->ADC_CR1 &=  ~( (1<<24)|(1<<25) ); //12-bit resolution
	ADC12->ADC_CR1 &= ~( (1<<13)|(1<<14)|(1<<15) ); //number of channels is 1
	ADC12->ADC_CR1 |= (1<<5); //interrupt enable for EOC

	//To start the ADC converter run the SWSTART
	//ADC12->ADC_CR2 |= (1<<30);

	//do not run the ADC Convertert
	ADC12->ADC_CR2 &= ~(1<<30);

	//no need to modify external input
	//external event used to trigger the start conversion of a regular group
	//will have to set data alignment for Right
	ADC12->ADC_CR2 &= ~(1<<11);

	//set the end of conversion
	ADC12->ADC_CR2 |= (1<<10);

	//set the adc to single conversion mode
	ADC12->ADC_CR2 &= ~(1<<1);

	//enable the ADC converter
	ADC12->ADC_CR2 |= (1<<0);

	// Set external trigger to TIM4 CC4
	ADC12->ADC_CR2 |= 0b1001 << 24;
	// Set external trigger to any edge
	ADC12->ADC_CR2 |= 0b11 << 28;

	//To setup for sampling time for channel 9 go to ADC_SMPR2
	//set it to 56 cycles in the start of the program
	//Note: 000: 3 cycles
	//		001: 15 cycles
	//		010: 28 cycles
	//		011: 56 cycles
	//		100: 84 cycles
	//		101: 112 cycles
	//		110: 144 cycles
	//		111: 480 cycles
	ADC12->ADC_SMPR2 |= ( (1<<27)|(1<<28) );

	//Sequence Register 1&2
	//Set it up for the Channel number 9 in regular sequence number
	//set it to be regular channel sequence length
	ADC12->ADC_SQR1 &= ~( (1<<20)|(1<<21)|(1<<22)|(1<<23) );
	ADC12->ADC_SQR3 |= 9; //set it to equal 9-no other bits relevant

	//To read the regular data register
	//ADC12->ADC_DR


	//ADC1 IRQ_n = 18 position value Address 0x0000 00B0
	NVIC_ISER[0] = 1<<18;

}


static void GPIO_init( void )
{
	RCC[RCC_AHB1ENR] |= (1 << 1); // Init the GPIO B RCC PIN
	RCC[RCC_APB2ENR] |= (1 << 8); // Init the ADC12_IN9 RCC clock

	//enable PB1 to analog
	GPIO_B[MODER] |= ( ( 1<<2 )|( 1<<3 ) );

	//no alternate function

	//setup the timer RCC CLOCKS
	// enable clock for TIM4 - bit 2 of APB1ENR
	RCC[RCC_APB1ENR] |= (1 << 2);
}


void ADC_START( void )
{
	//start conversion
	ADC12->ADC_CR2 |= (1<<30);
	TIM4->CR1 |= 1<<0; // CEN is bit 0
	Wave.WaveFormStarted = TRUE;

}


void  GET_WAVE( void )
{
	if(Wave.WaveFormStarted )
	{
		if(Wave.CaptureDone)
			{
				printf("Getting waveformData...\n");

				//go ahead and print the collected data into waveform info
				int i=0;
				printf("INDEX \t\t Voltage[V]\n ");
				for(i=0; i < Wave.Sampling_amount; i++)
				{
					//print a row and column
					//printf(" %d,\t\t %.2f\n ",
					//		i,( (Wave.RAW_DATA_ptr[i]*3.3F)/ADC_12_BIT_RES) );

					printf("\t\t%.2f\n ",
							((Wave.RAW_DATA_ptr[i]*3.3F)/ADC_12_BIT_RES));
				}
				//free waveform when done
				free(Wave.RAW_DATA_ptr);
				//reset the waveform
				Reset_Wave();
				printf("\n"); //formatting
			}
			else
			{
				//have not finished collecting data go ahead print not done yet
				printf("...not done collecting, Try again later\n");
			}
	}
	else
	{
		//free waveform when done
		free(Wave.RAW_DATA_ptr);
		printf("Waveform not started please run collect CMD"
				" before trying to run this command\n\n");
	}
	return;
}


int  WAVE_SETUP( uint32_t sampling, uint32_t sampling_rate )
{
	//based on the user input get the sampling amount and sampling rate
	Wave.Sampling_Rate = sampling_rate;
	Wave.Sampling_amount = sampling;

	//create dynamic memory for the raw_data
	Wave.RAW_DATA_ptr = NULL;
	Wave.CaptureDone = FALSE;

	//set the program to have no error
	Wave.SampleAmount_ErrorInfo = NO_ERROR;
	Wave.SampleRATE_ErrorInfo = NO_ERROR;

	//check if the sampling amount is within bounds
	if( Wave.Sampling_amount > MAX_NUMBER_OF_SAMPLES)
	{
		Wave.SampleAmount_ErrorInfo = SAMPLE_AMOUNT_TOO_BIG;
		printf("Sampling Amount is bigger than %d\n", MAX_NUMBER_OF_SAMPLES);
	}
	else if(Wave.Sampling_amount < MIN_NUMBER_OF_SAMPLES)
	{
		Wave.SampleAmount_ErrorInfo = SAMPLE_AMOUNT_TOO_LITTLE;
		printf("Sampling Amount is less than %d\n", MIN_NUMBER_OF_SAMPLES);
	}
	else
	{
		//free waveform when done
		free(Wave.RAW_DATA_ptr);
		Wave.RAW_DATA_ptr = (uint32_t*)malloc(sampling*sizeof(uint32_t));
	}

	//if it is within bounds go ahead and check the sampling rate
	//check if the sampling amount is within bounds
	if( Wave.Sampling_Rate > MAX_NUMBER_OF_SAMPLE_RATE)
	{
		Wave.SampleRATE_ErrorInfo = SAMPLE_FREQZ_TOO_BIG;
		printf("Sampling Rate is bigger than %d\n", MAX_NUMBER_OF_SAMPLE_RATE);
	}
	else if(Wave.Sampling_Rate < MIN_NUMBER_OF_SAMPLE_RATE)
	{
		Wave.SampleRATE_ErrorInfo = SAMPLE_FREQZ_TOO_LITTLE;
		printf("Sampling Rate is less than %d\n", MIN_NUMBER_OF_SAMPLE_RATE);
	}
	else
	{
		//go ahead and setup the timer with this sampling rate
		// Each tick is 1uS for 1MHZ clock signal
		// Samples/Second for one sample we can calculate
		//Calculation equation
		// ARR = 1MHZ/SAMPLERATE - 1
		TIM4->ARR = (F_500KHZ/Wave.Sampling_Rate)-1;
	}

	//waveinfo
	if( (Wave.SampleAmount_ErrorInfo > NO_ERROR) ||
		(Wave.SampleRATE_ErrorInfo   > NO_ERROR) )
	{
		return FALSE;
	}

	//check if the collect subroutine was already called?
	if(Wave.WaveFormStarted)
	{
		printf("Collect cmd already called this will overwrite current data,\n"
				"run getwave first");
		return FALSE;
	}

	return TRUE;
}


static void Reset_Wave( void )
{
	Wave.Sampling_Rate = 0;
	Wave.Sampling_amount = 0;

	//create dynamic memory for the raw_data
	Wave.RAW_DATA_ptr = NULL;
	Wave.CaptureDone = FALSE;

	//set the program to have no error
	Wave.SampleAmount_ErrorInfo = NO_ERROR;
	Wave.SampleRATE_ErrorInfo = NO_ERROR;
	Wave.WaveFormStarted = FALSE;
}


//initing TIMER4
static void TIMER_init( void )
{
  //setup for TIM4->TIM4 is 16-bits
  // at 500 KHz (instead of 16 MHz)
  TIM4->PSC = 31; // Divisor will be PSC+1 or 32

  //will have to setup the ARR to know the sampling rate for starting the ADC
  // Set CCR4 to 0 - whenever counter hits 0  there
  // will be a channel 4 compare event
  TIM4->CCR4 = 0;

  // Set compare mode for channel 4
  TIM4->CCMR2 |= 0b011 << 12; // toggle mode for OC4
  // Enable CC4 generation
  TIM4->CCER = 1<<12;// channel 4, CC4E == bit 12

}


//interrupt service routine for ADC1
void ADC_IRQHandler( void )
{
	static int counter = 0;
	ADC12->ADC_SR = 0;
	if( counter < (Wave.Sampling_amount) )
	{
		//go ahead and store the value inside the pointer
		Wave.RAW_DATA_ptr[counter] = ADC12->ADC_DR;
		counter++;
	}
	else
	{
		Wave.CaptureDone = TRUE;
		//top Counter
		TIM4->CR1 &= ~(1<<0); // stop counter, will also stop IRQs
		counter = 0;
	}

}

