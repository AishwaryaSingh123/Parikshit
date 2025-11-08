
#include "led.h"
#include "main.h"

// Initialize array of LEDs dynamically
LED* LED_Init_Array(uint8_t n)
{
    LED *arr = (LED*)malloc(n * sizeof(LED));
    if (arr == NULL) return NULL;

    for (uint8_t i = 0; i < n; i++) {
        arr[i].led_no = i;
        arr[i].status = (uint8_t*)malloc(sizeof(uint8_t));
        *(arr[i].status) = 0;

        // Map LEDs to pins manually (example mapping)
        if (i == 0) { arr[i].port = GPIOB; arr[i].pin = GPIO_PIN_0; }
        else if (i == 1) { arr[i].port = GPIOB; arr[i].pin = GPIO_PIN_7; }
        else if (i == 2) { arr[i].port = GPIOB; arr[i].pin = GPIO_PIN_14; }

        HAL_GPIO_WritePin(arr[i].port, arr[i].pin, GPIO_PIN_RESET);
    }
    return arr;
}

// Free allocated memory
void LED_Deinit_Array(LED *arr, uint8_t n)
{
    if (arr == NULL) return;
    for (uint8_t i = 0; i < n; i++) {
        free(arr[i].status);
    }
    free(arr);
}

// Turn ON LED
void LED_On(LED *led)
{
    *(led->status) = 1;
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
}

// Turn OFF LED
void LED_Off(LED *led)
{
    *(led->status) = 0;
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
}

// Toggle LED
void LED_Toggle(LED *led)
{
    if (*(led->status))
        LED_Off(led);
    else
        LED_On(led);
}

// Toggle LEDs alternatively m times
void LED_Toggle_Alternately(LED *led_array, uint8_t n, uint8_t m)
{
    for (uint8_t count = 0; count < m; count++) {
        for (uint8_t i = 0; i < n; i++) {
            if (i % 2 == count % 2)
                LED_On(&led_array[i]);
            else
                LED_Off(&led_array[i]);
        }
        HAL_Delay(500); // delay 500 ms
    }
}
