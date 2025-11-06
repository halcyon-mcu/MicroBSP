#include "gpio.h"

#include "pcr.h"
#include "util.h"

// SAFETY: This assumes that SYS1_Init has been called beforehand.
void GPIO_Init() {
  // FIXME: This doesn't seem to affect anything.
  // Set PS[16] to power on all quadrants of GPIO (enable clk)
  PCR_ClearPowerDown(16, 0b1111);

  // Start GIO
  setbit(uint32_t, GPIO_BASE + GPIO_GCR0_OFFSET, 0, 1);
}

// How many pins are in each set 'A' and 'B'
#define PINS_PER_SET 8

// Returns whether the pin falls into the 'A' set of pins.
static bool isPinA(gpio_pin_t pin) {
	return pin < PINS_PER_SET;
}

#define PIN_OFFSET(pin) (isPinA(pin) ? pin : pin - PINS_PER_SET)

#define DIR_OFFSET(pin) (isPinA(pin) ? GPIO_DIRA_OFFSET : GPIO_DIRB_OFFSET)
#define PULL_OFFSET(pin) (isPinA(pin) ? GPIO_PULDISA_OFFSET : GPIO_PULDISB_OFFSET)
#define DRAIN_OFFSET(pin) (isPinA(pin) ? GPIO_PDRA_OFFSET : GPIO_PDRB_OFFSET)
#define DSET_OFFSET(pin) (isPinA(pin) ? GPIO_DSETA_OFFSET : GPIO_DSETB_OFFSET)

void GPIO_SetDirection(gpio_pin_t pin, gpio_dir_t dir) {
	setbit(uint32_t, GPIO_BASE + DIR_OFFSET(pin), PIN_OFFSET(pin), dir);
}

void GPIO_SetOpenDrain(gpio_pin_t pin, bool isOpen) {
	setbit(uint32_t, GPIO_BASE + DRAIN_OFFSET(pin), PIN_OFFSET(pin), isOpen ? 1 : 0);
}

void GPIO_SetPullDisabled(gpio_pin_t pin, bool isDisabled) {
	setbit(uint32_t, GPIO_BASE + PULL_OFFSET(pin), PIN_OFFSET(pin), isDisabled ? 1 : 0);
}

void GPIO_SetHigh(gpio_pin_t pin, bool isHigh) {
	setbit(uint32_t, GPIO_BASE + DSET_OFFSET(pin), PIN_OFFSET(pin), isHigh ? 1 : 0);
}
