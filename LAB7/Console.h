/*
 * Console.h
 *
 *  Created on: Jan 5, 2023
 *      Author: jurado-garciaj
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#define MAX_LENGTH 255
#define READ_UPPER_CASE  "RMW"
#define READ_LOWER_CASE  "rmw"
#define WRITE_UPPER_CASE  "WMW"
#define WRITE_LOWER_CASE  "wmw"
#define DUMP_UPPER_CASE  "DM"
#define DUMP_LOWER_CASE  "dm"
#define EXAMPLE_UPPER_CASE  "EX"
#define EXAMPLE_LOWER_CASE  "ex"
#define PLAY_MUSIC_LOWER_CASE "play"
#define PLAY_MUSIC_UPPER_CASE "PLAY"
#define FREQZ_LOWER_CASE "freqz"
#define FREQZ_UPPER_CASE "FREQZ"


typedef enum
{
	RMW, //0
	WMW, //1
	DM,  //2
	LED,  //3
	EXAMPLE, //4
	HELP,  //5
	PLAY, //6
	MEASURE, //7
	NO_CMD,

} CMD;

void Read_Text( const char input_string[] );

#endif /* CONSOLE_H_ */
