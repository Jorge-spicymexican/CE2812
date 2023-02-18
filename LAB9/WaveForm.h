/*
 * WaveForm.h
 *
 *  Created on: Feb 1, 2023
 *      Author: jurado-garciaj
 */

#ifndef WAVEFORM_H_
#define WAVEFORM_H_



#define ADC_12_BIT_RES 4096
#define MAX_NUMBER_OF_SAMPLES 500
#define MIN_NUMBER_OF_SAMPLES 10

#define MAX_NUMBER_OF_SAMPLE_RATE 10000
#define MIN_NUMBER_OF_SAMPLE_RATE 10


typedef enum
{
	NO_ERROR,
	SAMPLE_AMOUNT_TOO_BIG,
	SAMPLE_AMOUNT_TOO_LITTLE,
	SAMPLE_FREQZ_TOO_BIG,
	SAMPLE_FREQZ_TOO_LITTLE,

} Errocode;


typedef struct
{
	uint32_t* RAW_DATA_ptr;
	char CaptureDone;
	char WaveFormStarted;
	uint32_t Sampling_amount;
	uint32_t Sampling_Rate;
	Errocode SampleAmount_ErrorInfo;
	Errocode SampleRATE_ErrorInfo;
}sWaveform;



void ADC12_IN9_init( void );
void ADC_START( void );
void GET_WAVE( void );
int  WAVE_SETUP( uint32_t sampling, uint32_t sampling_rate );

#endif /* WAVEFORM_H_ */
