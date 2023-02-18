/**
  ******************************************************************************
  * @file           : lcd.h
  * @brief          : Header for lcd.c file.
  *                   This file contains the functions needed to interface with
  *                   CE2812 lcd screen and uses STM32F411RE microprocessor
  ******************************************************************************
  * @attention
  *	Author: Jorge Jurado-Garcia
  *	Created on: Dec 13, 2022
  *
  ******************************************************************************
  */

#include "stdint.h"

#ifndef LCD_H_
#define LCD_H_

//LCD CMDS
#define CLEAR_DISPLAY 				 0x01
#define RETURN_HOME	  				 0x02
#define ENTRY_MODE_SET				 0x06
#define DISPLAY_ON					 0x0E
#define DISPLAY_CURSOR_ON 		 	 0x0C
#define DISPLAY_CURSOR_BLINKING_ON 	 0x0F
#define CURSOR_DISPLAY_SHIFT		 0x10
#define FUNCTION_SET_8_bits_2Lines	 0x38
#define SET_CGRAM_ADDRESS 			 0x40
#define SET_DDRAM_ADDRESS			 0x80
#define READ_BUSYFLAG				 0x00
#define WRITE_DATA_TO ADDRESS		 0x00
#define READ_DATA_FROM_RAM			 0x00
#define WAKE_UP						 0x3C

// Registers Boundary Addresses
#define RCC_BASE_ADDRESS		0x40023800

// GPIO Base Address
#define GPIO_H_BASE_ADDRESS 	0x40021C00
#define GPIO_E_BASE_ADDRESS 	0x40021000
#define GPIO_D_BASE_ADDRESS 	0x40020C00
#define GPIO_C_BASE_ADDRESS 	0x40020800
#define GPIO_B_BASE_ADDRESS 	0x40020400
#define GPIO_A_BASE_ADDRESS 	0x40020000

//RCC Offset address
#define RCC_CR			0
#define RCC_PLLCFGR		1
#define RCC_CFGR 		2
#define RCC_CIR 		3
#define RCC_AHB1RSTR 	4
#define RCC_AHB2RSTR 	5
#define RCC_APB1RSTR 	8
#define RCC_APB2RSTR 	9
#define RCC_AHB1ENR		12
#define RCC_AHB2ENR 	13
#define RCC_APB1ENR		16
#define RCC_APB2ENR 	17
#define RCC_AHB1LPENR	20
#define RCC_AHB2LPENR	21
#define RCC_APB1LPENR	24
#define RCC_APB2LPENR 	25


//GPIO Offset address
#define MODER 			0  //Port Configuration register for I/O direction mode
#define OTYPER 			1  //Port Output type of the I/O port
#define OSPEEDER 		2  //Port Configure the I/O output speed
#define PUPDR 			3  //Configure the I/O pull-up or pull down
#define IDR 			4  //Read value for Input value of the corresponding I/O
#define ODR 			5  //Port output data
#define BSRR			6  //Port bit/reset register
#define LCKR			7  //Port Configuration lock register
#define AFRL			8
#define AFRH			9

void LCD_Init( void );

void LCD_Clear( void );

void LCD_Home( void );

void LCD_Set_Position(unsigned char row, unsigned char column);

void LCD_Print_Char(uint32_t c);

void LCD_Print_String(const char* c, int Start_Row, int Start_Column);

void LCD_Print_num( int num);

#endif /* LCD_H_ */
