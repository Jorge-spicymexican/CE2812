/*
 * measure.h
 *
 *  Created on: Jan 31, 2023
 *      Author: jurado-garciaj
 */

#ifndef MEASURE_H_
#define MEASURE_H_

#define RAW_COUNT 11
#define DELTA_COUNT 10
#define F_SAMPLING_PER32_N8 0x0f
typedef struct
{
	uint32_t Raw_DATA[RAW_COUNT];
	uint32_t Delta_DATA[DELTA_COUNT];
	int Collection_Done;
	float measuredFreqz;
	int min_sample;
	int max_sample;
}sDatalog;



void TIM2_init( void );
void START_TIM2( void);
float Calculate_FREQZ( void);
int  ISR_DONE( void );
int Get_MinSample( void );
int Get_MaxSample( void );
void Clear_Log( void );

#endif /* MEASURE_H_ */
