/**
  ******************************************************************************
  * @file           : lcd.c
  * @brief          : source file.
  *                   This file contains the functions needed to interface with
  *                   CE2812 lcd screen and uses STM32F411RE microprocessor
  ******************************************************************************
  * @attention
  *	Author: Jorge Jurado-Garcia
  *	Created on: Dec 13, 2022
  *		PA4     ---> DB0
  *		PA5		---> DB1
  *		PA6		---> DB2
  *		PA7		---> DB3
  *		PA8		---> DB4
  *		PA9		---> DB5
  *		PA10	---> DB6
  *		PA11	---> DB7
  *		PC8		---> RS  (Register Select Signal RS=0:CMD RS=1:Data)
  *		PC9		---> R/W (Read/White Select Signal R/W=1:Read R/W=0:Write)
  *		PC10	---> E
  *
  *
  ******************************************************************************
  */

#include "lcd.h"
#include "delay.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "system.h"


//setup for of Pointers for System Registers
volatile uint32_t * const GPIO_A = (uint32_t*) GPIO_A_BASE_ADDRESS;
volatile uint32_t * const GPIO_C = (uint32_t*) GPIO_C_BASE_ADDRESS;

#define RS_HIGH		GPIO_C[ODR]|=  (1<<8)
#define RS_LOW  	GPIO_C[ODR]&= ~(1<<8)
#define READ_MODE	GPIO_C[ODR]&=  (1<<9)
#define WRITE_MODE	GPIO_C[ODR]&= ~(1<<9)
#define E_HIGH		GPIO_C[ODR]|=  (1<<10)
#define E_LOW		GPIO_C[ODR]&=  ~(1<<10)

//Static function prototypes
//required for init
static void Init_GPIO( void );
static void LCD_Write_Execute( uint32_t bits );
static void LCD_DATA(uint32_t data);
static void LCD_CMD(uint32_t cmd);

static void Init_GPIO( void )
{
	volatile uint32_t * RCC = (uint32_t*) RCC_BASE_ADDRESS;
	//init GPIO A and C
	RCC[RCC_AHB1ENR] |= (1<<0|1<<2);

	//setting up output pins
	GPIO_A[MODER] |= ( (1 << 8)	 | (1 << 10) | (1 << 12) | (1 << 14) |
					   (1 << 16) | (1 << 18) | (1 << 20) | (1 << 22) );

	GPIO_C[MODER] |= ( (1 << 16)| (1 << 18) | (1 << 20) );

}


static void LCD_Write_Execute( uint32_t bits )
{
	GPIO_A[ODR] &= ~(0xFF0);
	//simply do this...
	GPIO_A[ODR]|= (bits << 4);

	unsigned int i = 1;
	WRITE_MODE;
	E_HIGH;
	delay_us(i);
	E_LOW;

}


static void LCD_DATA(uint32_t data)
{

	RS_HIGH;
	LCD_Write_Execute( data );

}


static void LCD_CMD(uint32_t cmd)
{
	RS_LOW;
	LCD_Write_Execute( cmd );

}


void LCD_Init( void )
{
	unsigned int delay = 100;
	Init_GPIO();

	E_LOW;
	WRITE_MODE;
	RS_LOW;
	delay_ms(delay);

	delay = 10;
	LCD_CMD( WAKE_UP ); //Wake up - 1
	delay_ms(delay);
	LCD_CMD( WAKE_UP ); //Wake up - 2
	delay_ms(delay);


	LCD_CMD( DISPLAY_CURSOR_BLINKING_ON );
	delay_ms(delay);

	LCD_CMD( CLEAR_DISPLAY );
	delay_ms(delay);

	LCD_CMD( ENTRY_MODE_SET );
	delay_ms(delay);


}

void LCD_Clear( void )
{
	unsigned int delay = 2;
	LCD_CMD( CLEAR_DISPLAY ); //LCD clear
	delay_ms(delay);
}

void LCD_Home( void )
{
	unsigned int delay = 2;
	LCD_CMD( RETURN_HOME ); //LCD clear
	delay_ms(delay);
	LCD_Set_Position(0,0);
}

void LCD_Set_Position(unsigned char row, unsigned char column)
{
	unsigned int delay = 37;
	int instruction = (row * 0x40) + column + 0x80;
	LCD_CMD( instruction ); //LCD instruction
	delay_us(delay);
}

void LCD_Print_Char(uint32_t c)
{
	unsigned int delay = 37;
	LCD_DATA( c ); //vhar
	delay_us(delay);
}


void LCD_Print_String(const char* c, int Start_Row, int Start_Column)
{

	int Length = strlen(c);
	LCD_Set_Position(Start_Row, Start_Column);
	int n = 0;

	while (n != Length)
	{

		LCD_Print_Char( c[n] ); //print char
		Start_Column++;


		//go ahead an look around the string and increment to each column
		if( Start_Column > 16 )
		{
			Start_Row++;
			Start_Column = 0;
			if( Start_Row == 2 )
			{
				Start_Row = 0;
				LCD_Set_Position(Start_Row, Start_Column);
			}
			LCD_Set_Position(Start_Row, Start_Column);
		}
		n++;

	}

}


void LCD_Print_num( int num)
{
	char buffer[22];
	sprintf(buffer, "%d", num);

	int i = 0;
	// print every character in the string
	while (buffer[i] != '\0')
	{
		LCD_Print_Char(buffer[i++]);
	}


}

