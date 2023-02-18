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
	// The clock timer is shown to be 16MHz
	// Seconds TIMER_CLOCK = 1/16MHz
	// MAXIMUM TICKS TO BE ENABLED IS: 0x00FFFFFF ~ 16,777,215
	// MAX VALUE AFTER TICK EXPIRED:
	//setup for of Pointers for System Registers
	// Programming RELOAD value to the highest possible value for right now
	// the amount of time it would take for all ticks is 1.05 seconds
	// for one millisecond simply 0.001 sec * 16MHz = 16,000
	volatile uint32_t * const stk_ctrl = (uint32_t*) STK_CTRL;
	volatile uint32_t * const stk_load = (uint32_t*) STK_LOAD;
	//load value then start timer
	*stk_load = LOAD_VALUE_1_ms;

	// Setting up control register but number enabled
	*stk_ctrl |= (ENABLE_FIELD);

	for(int i=0; i < ms; i++)
	{
		//read the whole field and bit-mask this field
		// 1&0 is 0 1&1 = 1
		while( (*stk_ctrl & (1 << 16 )) == 0 )
		{
			; //do nothing
		}

	}

	// Setting up control register but number enabled
	*stk_ctrl &= ~(ENABLE_FIELD);
	//printf("Milli-Second Timer finished\n");
	//Timer finished
}

void delay_us( unsigned int us)
{

	volatile uint32_t * const stk_ctrl = (uint32_t*) STK_CTRL;
	volatile uint32_t * const stk_load = (uint32_t*) STK_LOAD;
	//load value then start timer
	// for one millisecond simply 0.001 sec * 16MHz = 16,000
	*stk_load = (LOAD_VALUE_1_ms/1000); //16

	// Setting up control register but number enabled
	*stk_ctrl |= (ENABLE_FIELD);

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

	volatile uint32_t * const stk_ctrl = (uint32_t*) STK_CTRL;
	volatile uint32_t * const stk_load = (uint32_t*) STK_LOAD;
	//load value then start timer
	// for one millisecond simply 0.001 sec * 16MHz = 16,000
	*stk_load = (LOAD_VALUE_1_ms*1000); //16,000 *1000

	// Setting up control register but number enabled
	*stk_ctrl |= (ENABLE_FIELD);

	for(int i=0; i < s; i++)
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
	//printf("One Second Timer finished\n");
	//Timer finished
}
