/*
 * led.h
 *
 *  Created on: Jan 12, 2023
 *      Author: jurado-garciaj
 */

#ifndef LED_H_
#define LED_H_

#include "stdint.h"

#define LOWER_BITS 63
#define HIGHER_BITS 960

/*
 * led_init()
 * Enables the LED on the CE2812 dev board by setting up RCC and GPIO to Outputs
 */
void led_init();

/*
 * led_allOn()
 * Turns on all of the leds
 */
void led_allOn();

/*
 * led_allOff()
 * turns off all of the leds
 */
void led_allOff();

/*
 * led_on()
 * Turns on one one led on the Light brick. Ranges from 0-11
 */
void led_on(uint8_t index);

/*
 * led_off()
 * Turn off one led on the light brick Ranges from 0-11
 */
void led_off(uint8_t index);


/*
 * led_ride()
 * 		Scan the light across and back at the current speed used for
 * 		Rider lighting
 */
void led_ride();


/*
 * led_setSpeed (uint8_t speed)
 * 		arg: speed (0 slow - 9 fast)
 * 		Args out of range should print error to console
 */
void led_setSpeed(uint8_t speed);


/*
 * getCurrentSpeed
 * 		returns the current speed
 */
uint8_t getCurrentSpeed();


#endif /* LED_H_ */
