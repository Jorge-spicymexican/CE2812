/*
 * Console.c
 *
 *  Created on: Jan 5, 2023
 *      Author: jurado-garciaj
 */

#include "stdio.h"
#include "stdint.h"
#include "Console.h"
#include "string.h"
#include "music.h"
#include "measure.h"
#include "WaveForm.h"

//static private prototypes
static void help( void );
static CMD cmd_parser( const char cmd[] );
static void Example( void );
static void Read_memory( uint32_t address);
static void write_memory( uint32_t address, uint32_t value);
static void Dump_memory( uint32_t address, uint32_t length);
static void print_binary(uint32_t n);
static void Play_music( uint32_t selection);
static void Measure_freqz( void );

static void Measure_freqz( void )
{
	START_TIM2();

	//do nothing
	while( !ISR_DONE() )
	{
		//do nothing
	}

	printf("Freqz (Hz): %.1f\n", Calculate_FREQZ() );

	//calculate the min and max value
	printf("Min Sample Value: %ul\n", Get_MinSample() );
	printf("Max Sample Value: %ul\n", Get_MaxSample() );
	Clear_Log();

}


static CMD cmd_parser( const char cmd[] )
{
	//cannot use switch case statment for string values
	// will have to be a nested if statement

	if( (strstr(cmd,READ_UPPER_CASE) != NULL) ||
		(strstr(cmd,READ_LOWER_CASE) != NULL) )
	{
		return RMW;
	}
	else if((strstr(cmd,WRITE_UPPER_CASE) != NULL) ||
			(strstr(cmd,WRITE_LOWER_CASE) != NULL) )
	{
		return WMW;
	}
	else if((strstr(cmd,DUMP_UPPER_CASE) != NULL) ||
			(strstr(cmd,DUMP_LOWER_CASE) != NULL) )
	{
		return DM;
	}
	else if((strstr(cmd,EXAMPLE_UPPER_CASE) != NULL) ||
			(strstr(cmd,EXAMPLE_LOWER_CASE) != NULL) )
	{
		return EXAMPLE;
	}
	else if((strstr(cmd,PLAY_MUSIC_UPPER_CASE) != NULL) ||
			(strstr(cmd,PLAY_MUSIC_LOWER_CASE) != NULL) )
	{
		return PLAY;
	}
	else if((strstr(cmd,FREQZ_LOWER_CASE) != NULL) ||
			(strstr(cmd,FREQZ_UPPER_CASE) != NULL) )
	{
		return MEASURE;
	}
	else if((strstr(cmd,WAVE_LOWER_CASE) != NULL) ||
			(strstr(cmd,WAVE_UPPER_CASE) != NULL) )
	{
		return GET_WAV;
	}
	else if((strstr(cmd,WAVE_COLLECT_LOWER_CASE) != NULL) ||
			(strstr(cmd,WAVE_COLLECT_UPPER_CASE) != NULL) )
	{
		return COLLECT_WAVE;
	}
	else
	{
		return HELP;
	}

	return NO_CMD;
}


static void print_binary(uint32_t n)
{
    int l = sizeof(n) * 8;
    for (int i = l - 1 ; i >= 0; i--) {
        printf("%lx", (n & (1 << i)) >> i);
    }
}

static void Read_memory( uint32_t address )
{
	uint32_t setter = address;
	volatile uint32_t * const Memory = (uint32_t*) setter;
	//read an unsigned 32-bit word at that address
	uint32_t value = *Memory;

	//print off address and value
	printf("%#lX %#lX %lu  ", address, value, value );

	//print it for binary format
	print_binary(value);
	printf("\n");
	return;

}


static void write_memory( uint32_t address, uint32_t value)
{
	uint32_t setter = address;
	volatile uint32_t* Memory = (uint32_t*) setter;

	//write the value in the address location
	*Memory |= (value);

	//read memory location
	Read_memory(setter);

	return;
}


static void Dump_memory( uint32_t address, uint32_t length)
{

	volatile uint32_t* Memory = (uint32_t*) address;

	// if no length supplied, will default to 16
	if(length <= 0)
	{
		length = 16;
	}

    int remainder = length % 4; //getting the remainder based on 4 bytes
    							// breakdown

    int increments = length/4; //increments for the address broken by 4 bytes


	for (int i = 0; i < increments; i++)
	{
		printf("0x%08lx: ", (unsigned long) Memory);
		for (int i = 3; i >= 0; i--)
		{
			//get the data at the addres and shift by 8 bits to the right
			// then mask off
			printf("%02lx ", ((*Memory >> i * 8) & 0xff)) ;
		}
		Memory += 0x01; //move onto the next index of the address
		//pointer arithmetic

		printf("\n");
	}


	// Dump remainder bytes of memory
	// Number of sets is based off 'remainder' quantity
	if (remainder > 0)
	{
		printf("0x%08lx: ", (unsigned long) Memory);
		for (int i = remainder-1; i >= 0; i--)
		{
			printf("%02lx ", ((*Memory >> i * 8) & 0xff) );
		}
		printf("\n");
	}
}

static void Play_music( uint32_t selection)
{
	//this is redundemt but its okay
	Console_show(selection);
}

static void Example( void )
{
	//example code sections
	printf("EXAMPLE CODE (EX) \n");
	printf("\t > DM 0x20000000 25 \n");
	printf("\t 0x20000000 01 11 1F 0E FF A0 55 80 23 43 E9 CD F0 DE AA 03\n\n");
	printf("\t > RMW 0x20000000 25 \n");
	printf("\t 0x20000000  0x0E1F1101  236916993   0b00001110000111110001000100000001\n\n");
	printf("\t > WMW 0x20000000 10 \n");
	printf("\t 0x20000000 0x0000000A 10 0b00000000000000000000000000001010\n\n");
	printf("\t > Play 1\n"); //plays scale

}


static void help( void )
{
	//print out Read Memory word description plus argurements
	printf("Read Memory Word (RMW) \n");
	printf("\t Arguments: uint32_t address \n");
	printf("\t Returns: uint32_t Word \n");
	printf("\t Description: User will provide an address and the program \n"
		   "\t\t will read an unsigned 32-bit word at that address and print\n"
		   "\t\t contents to the console in hex and decimal format.\n");
	printf("NOTE: This command will ensure it only reads addresses on a "
			"word boundary.\n\n\n");


	//print out write memory word and descriptions
	printf("Write Memory Word (WMW) \n");
	printf("\t Arguments: uint32_t address, uin32_t value \n");
	printf("\t Returns: uint32_t address, uint32_t value in \n "
			"\t hex, decimal. and binary \n");
	printf("\t Description: User will provide an address and value and \n"
		   "\t\t will write the provided value as an uint32_t word to address\n"
		   "\t\t contents will print on the console in hex, decimal,\n "
		   "\t\t& binary format.\n");
	printf("NOTE: This command will ensure it only write to addresses on a "
			"word boundary.\n\n");

	//print out dump memory function word and descriptions.
	printf("Dump Memory Word (DM) \n");
	printf("\t Arguments: uint32_t address, uint32_t length \n");
	printf("\t Returns: uint32_t Address Block \n");
	printf("\t Description: User will provide an address and length \n"
		   "\t\t will read an unsigned 32-bit address to the specified length\n"
		   "\t\t and dump the contents to the console. If no length is given\n "
		   "\t\t default is set to 16 bytes.\n\n");

	//help section
	printf("Help (Help) \n");
	printf("\t Arguments: void \n");
	printf("\t Returns: void \n");
	printf("\t Description: Provides the user with detailed help for using\n"
		   "\t\t program.\n\n");

	//example code sections
	printf("EXAMPLE CODE (EX) \n");
	printf("\t Description: Provides the user with examples of functionality\n"
		   "\t\t program.\n\n");

	printf("Play BackgrounMusic (Play) \n");
	printf("\t Description: Provides the user music selections and plays in"
			"\t\t the background.\n\n"
			"\t\t 1 - Scale\n"
			"\t\t 2 - SuperMarioBros\n"
			"\t\t 3 - A Thousands Years\n"
			"\t\t 4 - O' Christmas Tree\n\n");


	printf("Calculate Frequency (FREQZ) \n");
	printf("\t Description: Calculates the Frequency of the PA15 pin. Must be \n"
		   "\t a square wave.\n\n");

	printf("GetWaveFormData (GETWAVE) \n");
	printf("\t Description: Returns the waveform data being read from PB1.\n"
		   "\t User must run 'COLLECT' function first in order to collect\n "
		   "\t data.\n\n");

	printf("Collect WaveformData via ADC (COLLECT) \n");
	printf("\t Arguments: uint32_t SAMPLING NUMBER, uint32_t SAMPLING RATE \n");
	printf("\t Description: Sends request to start capturing data from PB1.\n"
		   "\t If the command is ran twice before running the collect command\n"
		   "\t the user will be notified that overwrites can happen and\n"
		   "\t recommend to get wave data first. SAMPLE NUMBER WILL BE IN HEX!"
		   "\n\n ");

}


void Read_Text( const char input_string[] )
{
	//read terminal input and then parse them into their respective bins
	// inputs are typically command type, address in hex, and integer
	uint32_t value = 0;
	uint32_t address = 0;
	char Command[MAX_LENGTH + 1];
	sscanf(input_string, "%s %lx %ld", Command, &address, &value);

	//will have to try to redo the COLLECT function since address is always
	//calculated as a hex instead of an integer

	CMD output = NO_CMD;
	output = cmd_parser( Command);

	//based on the output go into the correct function
	switch( output )
	{
	case RMW:
		Read_memory(address);
		break;

	case WMW:
		write_memory(address, value);
		break;

	case DM:
		Dump_memory(address, value);
		break;

	case EXAMPLE:
		Example();
		break;

	case HELP:
		help();
		break;

	case PLAY:
		Play_music(address);
		break;

	case MEASURE:
		Measure_freqz();
		break;

	case GET_WAV:
		//function call for getwave
		GET_WAVE();
		break;

	case COLLECT_WAVE:
		//function call for collect waves
		//						  sampling 			 rate
		if( WAVE_SETUP( (uint32_t)address, (uint32_t)value ) )
		{
			ADC_START();
		}
		break;
	default:
		printf("Error CMD was found to be Null");

	}
}
