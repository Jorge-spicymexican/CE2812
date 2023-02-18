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


static volatile uint32_t * const GPIO_B = (uint32_t*) GPIO_B_BASE_ADDRESS;

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


void light_led(uint32_t index)
{
	//turn off the timer

	//Clear register then put in value
	GPIO_B[BSRR] = (0xF7E00000); //turns off PB5-PB15, excluding PB11

	//bit mask these guys to get the correct values
	int BITS = (((index & 0x3F)<<5)|((index & 0x3C0)<<6)); //Masks ;

	//Clear register then put in value
	GPIO_B[BSRR] |= ( BITS);

	//turn on the timer
}



void led_ride()
{
	static int inc = 0;
	static int direction = 0; //up
	while(1)
	{
		delay_ms(100);
		light_led(1 << inc);
		delay_ms(100);

		if( inc == 9 )
		{
			direction = 1;
		}
		else if( inc == 0)
		{
			direction = 0;
		}

		if( !direction )
		{
			inc++;
		}
		else
		{
			inc--;
		}
	}
}

