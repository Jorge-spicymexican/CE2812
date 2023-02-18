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


int delay_int( void )
{
	//setup for of Pointers for System Registers
	volatile uint32_t * const stk_ctrl = (uint32_t*) STK_CTRL;

	// with the address set modify the needed values
	// SysTick CTRL register
	/*
	 *  BIT 31:17 -> Reserved, must be kept cleared
	 *  BIT 16    -> COUNTFLAGS, Returns 1 if timer reaches 0
	 *  BIT 15:03 -> Reserved, must be kept cleared
	 *  BIT 2 	  -> CLKSOURCES, Selects Clock sources, 0:AHB/8 1: AHB
	 *  BIT 1	  -> TICKINT, Enable bit for SysTick exception request
	 *  BIT 0 	  -> ENABLE, Enable the COUNTER
	 */

	// Setting up control register but number enabled
	*stk_ctrl |= (CLKSOURCE_FIELD);
	return 0;
}


void delay_ms( unsigned int ms )
{
	delay_us( ms*1000);
}

void delay_us( unsigned int us)
{

	volatile uint32_t * const stk_ctrl = (uint32_t*) STK_CTRL;
	volatile uint32_t * const stk_load = (uint32_t*) STK_LOAD;
	volatile uint32_t * const stk_val = (uint32_t*) STK_VAL;
	//load value then start timer
	// for one millisecond simply 0.001 sec * 16MHz = 16,000
	*stk_load = (LOAD_VALUE_1_ms/1000); //16

	// Setting up control register but number enabled
	*stk_ctrl |= (ENABLE_FIELD);

	//clear any current value that exist by writing any value
	*stk_val = 1;

	for(int i=0; i < us; i++)
	{
		//read the whole field and bitmask this field
		// 1&0 is 0 1&1 = 1
		// 1 indicates it was red
		while( (*stk_ctrl & (1 << 16 )) == 0)
		{
			; //do nothing
		}

	}
	*stk_ctrl &= ~(ENABLE_FIELD);
	//printf("Micro Second Timer finished\n");
	//Timer finished
}



void delay_sec( unsigned int s)
{

	delay_ms(1000*s);
}
