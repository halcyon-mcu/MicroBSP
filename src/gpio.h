#pragma once

#include <stdbool.h>
#include <stdint.h>

// Refer to 1303 of TRM for initialization steps

#define GPIO_BASE 0xFFF7BC00

#define GPIO_GCR0_OFFSET 0x00
#define GPIO_DIRA_OFFSET 0x34
#define GPIO_DIRB_OFFSET 0x54

#define GPIO_PDRA_OFFSET 0x48
#define GPIO_PDRB_OFFSET 0x68

#define GPIO_DSETA_OFFSET 0x40
#define GPIO_DSETB_OFFSET 0x60

#define GPIO_PULDISA_OFFSET 0x4C
#define GPIO_PULDISB_OFFSET 0x6C

void GPIO_Init();

typedef unsigned int gpio_pin_t;

typedef enum {
	// Interpretation on page 1323
	// Ensure you read the register documentation to see what each value maps to
	GPIO_DIR_INPUT = 0,
	GPIO_DIR_OUTPUT = 1,
} gpio_dir_t;

void GPIO_SetDirection(gpio_pin_t pin, gpio_dir_t pinDir);
void GPIO_SetPullDisabled(gpio_pin_t pin, bool isDisabled);
void GPIO_SetOpenDrain(gpio_pin_t pin, bool isOpenDrain);
void GPIO_SetHigh(gpio_pin_t pin, bool isHigh);
