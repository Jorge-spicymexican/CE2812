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
 * led_off()
 * Turn off one led on the light brick Ranges from 0-11
 */
void light_led(uint32_t index);


/*
 * led_ride()
 * 		Scan the light across and back at the current speed used for
 * 		Rider lighting
 */
void led_ride();



#endif /* LED_H_ */
