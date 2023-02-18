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


void LCD_Init( void );

void LCD_Clear( void );

void LCD_Home( void );

void LCD_Set_Position(unsigned char row, unsigned char column);

void LCD_Print_Char(uint32_t c);

void LCD_Print_String(const char* c, int Start_Row, int Start_Column);

void LCD_Print_num( int num);

#endif /* LCD_H_ */
