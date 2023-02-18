/**
  ******************************************************************************
  * @file           delay.c
  * @brief          source file for delay
  *
  ******************************************************************************
  * @attention
  *	Author Jorge Jurado-Garcia
  *	Created on: Dec 13, 2022
  *
  ******************************************************************************
  */

#include "delay.h"
#include <stdint.h>
#include "system.h"

static volatile TIMx* const TIM5 = (TIMx*) TIM5_BASE_ADDRESS;
static volatile SysTickx* const Ticky = (SysTickx*) SYSTICK_BASE_ADDRESS;
static volatile uint32_t* const NVIC_ISER = (uint32_t*) NVIC_BASE_ADDRESS;
static volatile unsigned int ticks = 0;
static volatile unsigned int flag = 0;

int delay_int( void )
{

	//init the sys-tick timer too for multitasking
	Ticky->STK_LOAD = (16000*20);
	Ticky->STK_VAL = 0;
	Ticky->STK_CTRL |= ( ( 1 << 1 )|( 1 << 2) );



	volatile uint32_t * const RCC = (uint32_t*) RCC_BASE_ADDRESS;
	RCC[RCC_APB1ENR] |= (1 << 3); // Init the TIM5 for RCC


	//to set the interrupt priority you will have to modify NVIC_IPR
	//This register provides an 8-bit field for each interrupt.
	//The location in which you should set the priority will be based on the
	//on the position value
	// EXAMPLE NVIC_IPR[29]
	// The processor only implements bits [7:4]
	// bits [3:0] reads as zeros
	// the lower the value the greater the priority of the interrupt

	//For this problem we will not have to implement any priority.

	//setting up the NVIC for the TIMER5
	//TIM3 IRQ_n = 50 position value Address 0x0000 00B4
	NVIC_ISER[1] = 1<<18;  //50/32

	// at 500 KHz (instead of 16 MHz)
	TIM5->PSC = 31; // Divisor will be PSC+1 or 32

	TIM5->CR1 &= ~(( 1 << 9) | (1 << 8) );
	//TIM5->CR1 |=  ( 1 << 7); //Auto reload bit on auto files in the ARR

	TIM5->CCMR1 |=  ( ( 1 << 5 ) | (1 << 4) ); //Output compare mode 1 mode

	TIM5->SR = 0;
	TIM5->DIER |= (1 << 0); //Enabled UI interrupt
	TIM5->CR1 &= ~(1<<0); // stop counter, will also stop IRQs

	//set the timer to have
	TIM5->ARR = 499;
	TIM5->CCR1 = 0;

	TIM5->SR = 0;

	Ticky->STK_CTRL |= ( 1 << 0);

	return 0;
}


void delay_ms( unsigned int ms )
{
	TIM5->SR = 0;
	TIM5->DIER |= (1 << 0); //Enabled UI interrupt
	TIM5->CR1 |= (1<<0); // start counter
	ticks = ms;
	while(!flag)
	{
		//do nothing
	}
	ticks = 0;
	flag = 0;
	return;
}



void TIM5_IRQHandler( void )
{
	//clear the CCMR1 interrupt flag
	//I am lazy we are just clearing all of the flags at this point
	TIM5->SR = 0;
	static unsigned int counter=0;
	//first count is always off so just do

	if( counter > (ticks-1) )
	{
		//set counter to zero
		counter = 0;
		TIM5->CR1 &= ~(1<<0); // stop counter
		TIM5->DIER &= ~(1 << 0); //Enabled UI interrupt
		flag = 1; //timer has expired
	}
	else
	{
		counter++;
	}

}

