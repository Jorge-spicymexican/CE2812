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

//preprocessors
/*
 * This information can be found on Section 4 of STM32 Programming Manual for
 * Cortex M-4 arm processor. Look at Section 4.1-> Table 36 for STM32 core
 * peripheral registers region.
 *
 * SysTick timers run at either processor clock of 16MHz by default or
 * processor clock divided by 8.
 */
#define STK_BASE_ADDRESS 0xE000E010
#define STK_CTRL STK_BASE_ADDRESS
#define STK_LOAD (STK_BASE_ADDRESS+0x04)
#define STK_VAL (STK_BASE_ADDRESS+0x08)
#define STK_CALIB (STK_BASE_ADDRESS+0x0C)

// CTRL Register
#define COUNTFLAG_FIELD 0x10000
#define CLKSOURCE_FIELD 0x04
#define TICKINT_FIELD 0x02
#define ENABLE_FIELD 0x01

#define LOAD_VALUE_1_ms 16000

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


/** @brief delay function for us delays.

 *  @param number of ticks per us
 *  @return void
 */
void delay_us( unsigned int us);


/** @brief delay function for s delays.

 *  @param number of ticks per s
 *  @return void
 */
void delay_sec( unsigned int s);


#endif /* INC_DELAY_H_ */
