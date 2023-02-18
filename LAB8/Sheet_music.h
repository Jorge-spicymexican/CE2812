/*
 * notes.h
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */

#ifndef SHEET_MUSIC_H_
#define SHEET_MUSIC_H_


//taken from the imperial  march code and information and modified it
//modified to include sharp notes
//looking to generate a function that auto calculates these values
// for octives simple just bit shift the value

//for octive equation
// Notes * (1 << Octive_x)
// difference between notes are not consisist so i will just
// have to me the zero octive as a const value and use those for my code


// C1 - C0
//32.70 - 16.35 = 16.35

// C2 - C0
//65.41 - 16.35 = 49.06

// C2 - C1
//65.41 - 32.70 = 32.71

// C3 - C2
//130.81 - 65.41 = 65.4

//extern sTone SCALE;
//extern sTone A_Thousand_Years;
//extern sTone Mario;
//extern sTone ChristmasTree;

#endif /* SHEET_MUSIC_H_ */
