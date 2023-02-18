/**
  ******************************************************************************
  * @file    main.c
  * @author  Jorge Jurado-Garcia
  * @brief   Default main function.
  *
  * Summary: This lab was a little bit difficult for me when starting out
  * 		 mostly due to getting used to the MCU as well as learning how to
  * 		 access its peripheral via pointers. From previous classes such as
  * 		 EE2920 we mostly using the a typedef structure and referenced to
  * 		 a variable inside the structure to manipulate the peripherals.
  * 		 Nevertheless, after playing around with ICECube and learning how
  * 		 to read the data sheet for the MCU i was able to figure out the
  * 		 specific address that needed to be changed. Afterwards, I have was
  * 		 able to complete the light_LED successfully by changing masking the
  * 		 bits to two sections and then shifting them by either 5 or 6
  * 		 depending on the masking value. Once done I simply used the OR
  * 		 operation to the values together. overall, I learned a lot from this
  * 		 lab and I hope to learn more on the next one.
  *
  ******************************************************************************
*/


#include <stdio.h>
#include <stdlib.h>
#include "uart_driver.h"

#define F_CPU 16000000UL
#define Half_Second_Iteration (F_CPU/2)
#define LOWER_BITS 63
#define HIGHER_BITS 960
#define PORTB (AHB1PERIPH_BASE + 0x0400UL)

// for adddress location go to Table21 section 6.3.22 RCC register map
//STM32F411%20Reference%20Manual.pdf
#define RCC_PERIPHERAL 0x40023800 //0x40023800
#define RCC_B1ENR (RCC_PERIPHERAL + 0x30 )

#define GPIOB 0x40020400
#define GPIOB_MODER (GPIOB + 0x00)
#define GPIOB_ODR (GPIOB + 0x14)



void delay_500ms( void );
void light_LED(int leds);
void light_LED_init( void );


int main( void )
{
	init_usart2(57600,F_CPU);
	light_LED_init();

	while(1)
	{
		int iterations = 0;
		printf("Enter the number of iterations..plz!\n");
		scanf("%d", &iterations);

		printf("You selected: %d\n", iterations);

		for(int i = 0; i < iterations; i++)
		{
			//counting upwards
			for( int j = 1; j < 10; j++)
			{
				//for each iterations go ahead and loop around each time
				light_LED( (1 << j) );
				delay_500ms();

			}

			//counting downwards
			for( int j = 9; j >= 0; j--)
			{
				//for each iterations go ahead and loop around each time
				light_LED( (1 << j) );
				delay_500ms();

			}

			printf("Iterations: %d Completed!\n", i+1);
		}

		light_LED( 0 );
	}

} //end of main


/** @brief Initializes the delay module in milli-seconds
 *
 * Assuming that the F_CPU is 16 MHz. To find the number of indices
 * have half a second just use this formula:
 * F_TIMER = 1/F_CPU = 1/16 MHZ = 0.0625 us
 *
 *  @param void
 *  @return void
 */
void delay_500ms( void )
{
	for(int i=0; i < (Half_Second_Iteration/100); i++ )
	{
		//do nothing
	}
}

/** @brief Turns on the leds to achieve the knight rider effect by bit shifting.

 *  @param int LEDS Value
 *  @return void
 */
void light_LED(int leds)
{
	//bit mask these guys to get the correct values
	unsigned int BITS = 0;
	BITS |= (leds & LOWER_BITS) << 5;
	BITS |= (leds & HIGHER_BITS) << 6;

	//Clear register then put in value
	uint32_t *GPIOB_MAP = (uint32_t*)GPIOB_ODR;
	*GPIOB_MAP &= ~( 0xFFFF);
	*GPIOB_MAP |= ( BITS);


	/*
	int pins[10] = {0,0,0,0,0,0,0,0,0,0};
	unsigned int Bits = 0;
	// if leds is 2 the remainder would be 0
	// so pin[0] = 0
	// if leds is 1 the reminder would be 1
	// so pin[1] = 1
	// highest number that leds can be in this situation is 65535
	for( int i=0; leds > 0; i++ )
	{
		pins[i] = leds % 2;
		leds = leds/2;
	}

	// pin[0] -> GPIOB.5
	// pin[1] -> GPIOB.6
	// pin[2] -> GPIOB.7
	// pin[3] -> GPIOB.8
	// pin[4] -> GPIOB.9
	//
	// pin[5] -> GPIOB.10
	// pin[6] -> GPIOB.12
	// pin[7] -> GPIOB.13
	// pin[8] -> GPIOB.14
	// pin[9] -> GPIOB.15
	//
	// First them to do is to simply bit shift by 5
	//

	for( int i=0; i < 10; i++)
	{
		// bit shift to the left by 5
		if( i < 6)
		{
			Bits += pins[i] << (i + 5);
		}
		else
		{
			Bits += pins[i] << (i + 6);
		}
	}
	 */
}


/** @brief Initializes the GPIO pins in port B for Lab along with
 * 			enabling the clock for the port
 *
 * Init the GPIO ports, which include enabling the clocks
 * setting the mode to output
 * must create pointer(s) as local variables, assign the I/O register's address
 * to the pointer, then dereference the pointers to modify the I/O registers.
 *
 *  @param void
 *  @return void
 */
void light_LED_init( void )
{
		// enabling the Clock for PORTB
		// To enable the GPIOB clock reference the table 6.3.10 RCC
		//AHB1 peripheral clock
		// enable register (RCC_AHB1ENR) in order to enable this register
		//we will have to change field 1
		uint32_t *RCC_REGISTER_MAP = (uint32_t*)RCC_B1ENR;
		*RCC_REGISTER_MAP |= ( 1 << 1 );

		// Setting PIN PB5, PB6, PB7, PB8, PB9, PB10, PB12, PB13, PB14, PB15
		// turning on the GPIO pins for this PORTB
		// We will have to modify the MODER register, this register is
		//responsible for configuration of different modes
		// For different modes are
		//00: input,
		//01: general purpose output mode
		//10: Alternate function mode
		//11: Analog mode
		//
		// this register is 32 bits with each two bits corresponded to a pin
		// so like for PINB.0 to be an output we will have to
		//modify MODER0 = 1 MODER1 = 0
		uint32_t *GPIO_B_REGISTER_MAP = (uint32_t*)GPIOB_MODER;
		*GPIO_B_REGISTER_MAP |= (1<<30); //Setting PINB15 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<28); //Setting PINB14 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<26); //Setting PINB13 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<24); //Setting PINB12 as output (01)

		*GPIO_B_REGISTER_MAP |= (1<<20); //Setting PINB10 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<18); //Setting PINB9 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<16); //Setting PINB8 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<14); //Setting PINB7 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<12); //Setting PINB6 as output (01)
		*GPIO_B_REGISTER_MAP |= (1<<10); //Setting PINB5 as output (01)

		// We can also setup the GPIO port output type registers but it
		//is not needed the reset value for these registers are 0x0000 0000
		//look into table 7.4.2 for more information
		// no need to write change the drain type

		// GPIO port pull-up/pull-down register labeled as GPIOx_PUPDR
		// This changes if its Pull-uo to VCC or Pull-Down to ground
		// reset value: 0x0000 0100
		// will have to change bits 11:10
		//GPIOB->PUPDR &= ~( (1<<10) | (1<<11) );

		// To run on all of the pins as a logic high
		// change the GPIO port output data register(GPIOx_ODR)
		// the bits 15-31 are reserved and should not be modified
		// bits 0-15 corresponds to the port pins and each indicate one pin
		// Example: ODR0 -> Px.0
		//uint32_t *GPIOB_MAP = (uint32_t*)GPIOB_ODR;
		//*GPIOB_MAP |= ( 0xFFFF);


}
