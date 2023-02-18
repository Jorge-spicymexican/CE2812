/*
 * led.c
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */


#include "led.h"
#include "system.h"
#include "stdint.h"
#include "delay.h"

#define GPIOB 0x40020400
#define GPIOB_MODER (GPIOB + 0x00)
#define GPIOB_ODR (GPIOB + 0x14)

static volatile uint32_t * const GPIO_B = (uint32_t*) GPIO_B_BASE_ADDRESS;

static uint8_t CurrentSpeed = 5;


static uint8_t check_index( uint8_t index);


static uint8_t check_index( uint8_t index)
{
	if( index > 12 )
	{
		return 12;
	}

	return index;
}

void led_init()
{
	volatile uint32_t * const RCC = (uint32_t*) RCC_BASE_ADDRESS;
	RCC[RCC_AHB1ENR] |= ( 1 << 1);
	GPIO_B[MODER] |= (1<<30); //Setting PINB15 as output (01)
	GPIO_B[MODER] |= (1<<28); //Setting PINB14 as output (01)
	GPIO_B[MODER] |= (1<<26); //Setting PINB13 as output (01)
	GPIO_B[MODER] |= (1<<24); //Setting PINB12 as output (01)

	GPIO_B[MODER] |= (1<<20); //Setting PINB10 as output (01)
	GPIO_B[MODER] |= (1<<18); //Setting PINB9 as output (01)
	GPIO_B[MODER] |= (1<<16); //Setting PINB8 as output (01)
	GPIO_B[MODER] |= (1<<14); //Setting PINB7 as output (01)
	GPIO_B[MODER] |= (1<<12); //Setting PINB6 as output (01)
	GPIO_B[MODER] |= (1<<10); //Setting PINB5 as output (01)

}


void led_allOn()
{
	GPIO_B[ODR] |= (0xF7E0);
}


void led_allOff()
{
	GPIO_B[ODR] &= ~(0xF7E0);
}


void led_on(uint8_t index)
{
	index = check_index(index);
	//bit mask these guys to get the correct values
	uint32_t BITS = 0;
	BITS |= (index & LOWER_BITS)  << 5;
	BITS |= (index & HIGHER_BITS) << 6;

	//Clear register then put in value
	GPIO_B[ODR] |= ( BITS);
}


void led_off(uint8_t index)
{
	index = check_index(index);
	//bit mask these guys to get the correct values
	uint32_t BITS = 0;
	BITS |= (index & LOWER_BITS) << 5;
	BITS |= (index & HIGHER_BITS) << 6;

	//Clear register then put in value
	GPIO_B[ODR] &= ~( BITS);
}



void led_ride()
{
	//Clear register then put in value
	uint32_t *GPIOB_MAP = (uint32_t*)GPIOB_ODR;

	//counting upwards
	for( int j = 1; j < 12; j++)
	{
		//bit mask these guys to get the correct values
		unsigned int BITS = 0;
		BITS |= (j & LOWER_BITS) << 5;
		BITS |= (j & HIGHER_BITS) << 6;


		*GPIOB_MAP &= ~( 0xFFFF);
		*GPIOB_MAP |= ( BITS);
		delay_us( 10000 - (90 * CurrentSpeed ) );

	}

	//counting downwards
	for( int j = 12; j >= 0; j--)
	{
		//bit mask these guys to get the correct values
		unsigned int BITS = 0;
		BITS |= (j & LOWER_BITS) << 5;
		BITS |= (j & HIGHER_BITS) << 6;

		//Clear register then put in value
		*GPIOB_MAP &= ~( 0xFFFF);
		*GPIOB_MAP |= ( BITS);

		delay_us( 10000 - (90 * CurrentSpeed ) );
	}
}



void led_setSpeed(uint8_t speed)
{
	if( (speed < 9) ) // do not need to check if its less then zero
	{
		CurrentSpeed = speed;
	}

}



uint8_t getCurrentSpeed()
{
	return CurrentSpeed;
}
