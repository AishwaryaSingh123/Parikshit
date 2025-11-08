
/*
 * led.h
 *
 *  Created on: Nov 6, 2025
 *      Author: aishw
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32h7xx_hal.h"
#include <stdlib.h>

// LED structure
typedef struct {
    uint8_t led_no;      // LED number (index)
    GPIO_TypeDef *port;  // Port to which LED is connected
    uint16_t pin;        // Pin number
    uint8_t *status;     // Pointer to LED status (0 = OFF, 1 = ON)
} LED;

// Function prototypes
LED* LED_Init_Array(uint8_t n);
void LED_Deinit_Array(LED *arr, uint8_t n);
void LED_On(LED *led);
void LED_Off(LED *led);
void LED_Toggle(LED *led);
void LED_Toggle_Alternately(LED *led_array, uint8_t n, uint8_t m);

#endif /* INC_LED_H_ */
