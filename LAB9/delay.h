/**
  ******************************************************************************
  * @file           delay.h
  * @brief          Header for delay.c file.
  *                   This file contains the delay timers and uses STM32F411RE
  ******************************************************************************
  * @attention
  *	Author Jorge Jurado-Garcia
  *	Created on Dec 13, 2022
  *
  ******************************************************************************
  */
#ifndef INC_DELAY_H_
#define INC_DELAY_H_



/** @brief Initializes the Systick timer for delaying functionality

 *  @param void
 *  @return success/fail
 */
int delay_int( void );


/** @brief delay function for ms delays.

 *  @param number of ticks per ms
 *  @return void
 */
void delay_ms( unsigned int ms );



#endif /* INC_DELAY_H_ */
