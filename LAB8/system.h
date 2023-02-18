/*
 * system.h
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define F_CPU 16000000UL
#define F_1MHZ 1000000UL
#define F_500KHZ 500000

// Registers Boundary Addresses
#define RCC_BASE_ADDRESS 0x40023800

// GPIO Base Address
#define GPIO_H_BASE_ADDRESS 0x40021C00
#define GPIO_E_BASE_ADDRESS 0x40021000
#define GPIO_D_BASE_ADDRESS 0x40020C00
#define GPIO_C_BASE_ADDRESS 0x40020800
#define GPIO_B_BASE_ADDRESS 0x40020400
#define GPIO_A_BASE_ADDRESS 0x40020000

//RCC Offset address
#define RCC_CR 0
#define RCC_PLLCFGR 1
#define RCC_CFGR 2
#define RCC_CIR 3
#define RCC_AHB1RSTR 4
#define RCC_AHB2RSTR 5
#define RCC_APB1RSTR 8
#define RCC_APB2RSTR 9
#define RCC_AHB1ENR 12
#define RCC_AHB2ENR 13

#define RCC_APB1ENR 16
#define RCC_APB2ENR 17
#define RCC_AHB1LPENR 20
#define RCC_AHB2LPENR 21
#define RCC_APB1LPENR 24
#define RCC_APB2LPENR 25

//GPIO Offset address
#define MODER 0 //Port Configuration register for I/O direction mode
#define OTYPER 1 //Port Output type of the I/O port
#define OSPEEDER 2 //Port Configure the I/O output speed
#define PUPDR 3 //Configure the I/O pull-up or pull down
#define IDR 4 //Read value for Input value of the corresponding I/O
#define ODR 5 //Port output data
#define BSRR 6 //Port bit/reset register
#define LCKR 7 //Port Configuration lock register
#define AFRL 8
#define AFRH 9

//used for TIM 2-5
#define TIM3_BASE_ADDRESS  0x40000400
#define TIM4_BASE_ADDRESS  0x40000800
#define TIM2_BASE_ADDRESS  0x40000000
#define TIM1_BASE_ADDRESS  0x40010000
//use for ADC14
#define ADC1_BASE_ADDRESS  0x40012000

//NVIC base address
#define NVIC_BASE_ADDRESS 0xE000E100

typedef struct
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t RES_0;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t RES_1;
	uint32_t DCR;
	uint32_t DMAR;
	uint32_t OR;

} TIMx;


typedef struct
{
	uint32_t ADC_SR;
	uint32_t ADC_CR1;
	uint32_t ADC_CR2;
	uint32_t ADC_SMPR1;
	uint32_t ADC_SMPR2;
	uint32_t ADC_JOFR1;
	uint32_t ADC_JOFR2;
	uint32_t ADC_JOFR3;
	uint32_t ADC_JOFR4;
	uint32_t ADC_HTR;
	uint32_t ADC_LTR;
	uint32_t ADC_SQR1;
	uint32_t ADC_SQR2;
	uint32_t ADC_SQR3;
	uint32_t ADC_JSQR;
	uint32_t ADC_JDR1;
	uint32_t ADC_JDR2;
	uint32_t ADC_JDR3;
	uint32_t ADC_JDR4;
	uint32_t ADC_DR;
	uint32_t ADC_CCR;

} ADCx;

#endif /* SYSTEM_H_ */
