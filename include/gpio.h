#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * Type definitions
 */

/**
 * GPIO Pins.
 */
typedef enum {
	GPIOA_0 = 0,
	GPIOA_1 = 1,
	GPIOA_2 = 2,
	GPIOA_3 = 3,
	GPIOA_4 = 4,
	GPIOA_5 = 5,
	GPIOA_6 = 6,
	GPIOA_7 = 7,
	GPIOB_0 = 8,
	GPIOB_1 = 9,
	GPIOB_2 = 10,
	GPIOB_3 = 11,
	GPIOB_4 = 12,
	GPIOB_5 = 13,
	GPIOB_6 = 14,
	GPIOB_7 = 15
} gpio_pin_t;

typedef enum {
	// Interpretation on page 1323
	// Ensure you read the register documentation to see what each value maps to
	GPIO_DIR_INPUT = 0,
	GPIO_DIR_OUTPUT = 1,
} gpio_dir_t;

/**
 * GPIO Initialization function. This must be called a single time upon reset.
 *
 * # SAFETY
 * This assumes that SYS1_Init has been called beforehand.
 */
void GPIO_Init();

void GPIO_SetDirection(gpio_pin_t pin, gpio_dir_t pinDir);
void GPIO_SetPullDisabled(gpio_pin_t pin, bool isDisabled);
void GPIO_SetOpenDrain(gpio_pin_t pin, bool isOpenDrain);
void GPIO_SetHigh(gpio_pin_t pin, bool isHigh);

#ifdef __cplusplus
}
#endif
