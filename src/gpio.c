#include "gpio.h"

#include "pcr.h"
#include "util.h"

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

#define GPIO_PULSELA_OFFSET 0x50
#define GPIO_PULSELB_OFFSET 0x70

#define GPIO_DCLRA_OFFSET 0x44
#define GPIO_DCLRB_OFFSET 0x64

void GPIO_Init() {
	// Set PS[16] to power on all quadrants of GPIO (enable clk)
	PCR_ClearPowerDown(16, 0b1111);

	// Start GIO
	set(uint32_t, GPIO_BASE + GPIO_GCR0_OFFSET, 1);
}

// How many pins are in each set 'A' and 'B'
#define PINS_PER_SET 8

// Returns whether the pin falls into the 'A' set of pins.
#define IS_PIN_A(pin) (pin < PINS_PER_SET)
#define PIN_OFFSET(pin) (IS_PIN_A(pin) ? pin : pin - PINS_PER_SET)

#define DIR_OFFSET(pin) (IS_PIN_A(pin) ? GPIO_DIRA_OFFSET : GPIO_DIRB_OFFSET)

#define PULLDIS_OFFSET(pin) (IS_PIN_A(pin) ? GPIO_PULDISA_OFFSET : GPIO_PULDISB_OFFSET)
#define PULLSEL_OFFSET(pin) (IS_PIN_A(pin) ? GPIO_PULSELA_OFFSET : GPIO_PULSELB_OFFSET)

#define DRAIN_OFFSET(pin) (IS_PIN_A(pin) ? GPIO_PDRA_OFFSET : GPIO_PDRB_OFFSET)

#define DSET_OFFSET(pin) (IS_PIN_A(pin) ? GPIO_DSETA_OFFSET : GPIO_DSETB_OFFSET)
#define DCLR_OFFSET(pin) (IS_PIN_A(pin) ? GPIO_DCLRA_OFFSET : GPIO_DCLRB_OFFSET)

static uint32_t currentDirectionState = 0;
void GPIO_SetDirection(gpio_pin_t pin, gpio_dir_t dir) {
	if (dir == GPIO_DIR_OUTPUT) {
		currentDirectionState |= (1 << PIN_OFFSET(pin));
	} else {
		currentDirectionState &= ~(1 << PIN_OFFSET(pin));
	}

	set(uint32_t, GPIO_BASE + DIR_OFFSET(pin), currentDirectionState);
}

static uint32_t currentOpenDrainState = 0;
void GPIO_SetOpenDrain(gpio_pin_t pin, bool isOpen) {
	if (isOpen) {
		currentOpenDrainState |= (1 << PIN_OFFSET(pin));
	} else {
		currentOpenDrainState &= ~(1 << PIN_OFFSET(pin));
	}

	set(uint32_t, GPIO_BASE + DRAIN_OFFSET(pin), currentOpenDrainState);
}

void GPIO_SetPullDisabled(gpio_pin_t pin, bool isDisabled) {
	if (isDisabled) {
		set(uint32_t, GPIO_BASE + PULLDIS_OFFSET(pin), 1 << PIN_OFFSET(pin));
	} else {
		set(uint32_t, GPIO_BASE + PULLSEL_OFFSET(pin), 0 << PIN_OFFSET(pin));
	}
}

void GPIO_SetHigh(gpio_pin_t pin, bool isHigh) {
	if (isHigh) {
		set(uint32_t, GPIO_BASE + DSET_OFFSET(pin), 1 << PIN_OFFSET(pin));
	} else {
		set(uint32_t, GPIO_BASE + DCLR_OFFSET(pin), 1 << PIN_OFFSET(pin));
	}
}
