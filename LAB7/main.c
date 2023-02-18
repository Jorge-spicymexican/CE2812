/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @Summary
 * 			This lab was pretty fun, I was able to get the interrupt
 * 			initialized and working with ease and calculating the frequency of
 * 			my Timer but ran into some issues when trying to get
 * 			accurate results. I was able to get the TIMER2 to work accurately
 * 			after I enabled and disabled my interrupt instead of stopping
 * 			the timer. With changing of the the CCMR1 Input register sampling
 * 			to event to none and having a high input filter. I was able to
 * 			accurately read the frequency from my Analog to Discovery
 * 			Waveform. Looks like it works really good for lower frequency
 * 			and decent for higher frequencies. At 10KHz, the signal still
 * 			gets captured accurately but is: +/- 250 Hz.
 *
 *
 *@DatasheetNotes
 *			Interrupts are asynchronous events that disrupt the normal flow
 *			of your program. Allows MCY to focus on a key task and attend to
 *			the events as they come and needed.
 *
 *			To setup an interrupt on the F411 Board
 *			1. Configure the peripheral and enable the interrupt in the
 *				peripheral.
 *			2. Take note of the position and name of the interrupt on Table 37
 *				from chapter 10 of the technical reference manual.
 *				The position is the IRQn and the acronym is the predefined
 *				function ISR.
 *			3. Set the interrupt priority by writing on the interrupt priority
 *				register NVIC->IP
 *			4. Enable the interrupt itself by setting the
 *				appropriate NVIC->ISER bit. The value in which you
 *				should activate your value is based on the position value.
 *				  NVIC->ISER[IRQn >> 5] |= (1 << (IRQn % 32).
 *			5. Define your interrupt handler or ISR in your main.
 *
 ******************************************************************************
 */

//Note looks like the Piezo speaker is connected to PB4

#include <stdint.h>
#include "stdio.h"
#include "system.h"
#include "music.h"
#include "delay.h"
#include "Sheet_music.h"
#include "led.h"
#include "console.h"
#include "uart_driver.h"
#include "measure.h"



int main(void)
{
	init_usart2(57600, F_CPU);
	TIM2_init();
	//START_TIM2();
	TIM3_init();
	char data[MAX_LENGTH];
	int again = 0;

	while(1)
	{


		//polling to check if the music has finished
		if( !Music_status() )
		{
			//if music has finished notify that the user tha music is done
			printf("Music has finished playing\n");
			printf("Play MUSIC AGAIN: \n");
			again = 1;
		}
		else
		{
			//if the music is still playing
			printf("Enter your CMD: \n");
			fgets(data,MAX_LENGTH,stdin); //input from stdin stream
			printf("%s \n", data);
			Read_Text(data);
		}

		if( again )
		{
			//if the music is still playing
			printf("Enter your CMD: \n");
			fgets(data,MAX_LENGTH,stdin); //input from stdin stream
			printf("%s \n", data);
			Read_Text(data);
			again = 0;
		}

	}
}

