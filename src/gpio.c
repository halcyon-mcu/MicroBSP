#include "gpio.h"

#include "util.h"

// Refer to 1303 of TRM for initialization steps
typedef struct {
	volatile uint32_t GCR0;		 // 00h
	volatile uint32_t reserved1; // 04h
	volatile uint32_t INTDET;	 // 08h
	volatile uint32_t POL;		 // 0Ch
	volatile uint32_t ENASET;	 // 10h
	volatile uint32_t ENACLR;	 // 14h
	volatile uint32_t LVLSET;	 // 18h
	volatile uint32_t LVLCLR;	 // 1Ch
	volatile uint32_t FLG;		 // 20h
	volatile uint32_t OFF1;		 // 24h
	volatile uint32_t OFF2;		 // 28h
	volatile uint32_t EMU1;		 // 2Ch
	volatile uint32_t EMU2;		 // 30h
	volatile uint32_t DIRA;		 // 34h
	volatile uint32_t DINA;		 // 38h
	volatile uint32_t DOUTA;	 // 3Ch
	volatile uint32_t DSETA;	 // 40h
	volatile uint32_t DCLRA;	 // 44h
	volatile uint32_t PDRA;		 // 48h
	volatile uint32_t PULDISA;	 // 4Ch
	volatile uint32_t PULSELA;	 // 50h
	volatile uint32_t DIRB;		 // 54h
	volatile uint32_t DINB;		 // 58h
	volatile uint32_t DOUTB;	 // 5Ch
	volatile uint32_t DSETB;	 // 60h
	volatile uint32_t DCLRB;	 // 64h
	volatile uint32_t PDRB;		 // 68h
	volatile uint32_t PULDISB;	 // 6Ch
	volatile uint32_t PULSELB;	 // 70h
} gpio_register_t;

gpio_register_t* const gpioREG = (gpio_register_t*)(uintptr_t)(0xFFF7BC00UL);

STATIC_ASSERT(offsetof(gpio_register_t, GCR0) == 0x00, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, DIRA) == 0x34, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, DIRB) == 0x54, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, PDRA) == 0x48, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, PDRB) == 0x68, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, DSETA) == 0x40, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, DSETB) == 0x60, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, PULDISA) == 0x4C, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, PULDISB) == 0x6C, invalid_offset);
STATIC_ASSERT(offsetof(gpio_register_t, PULSELA) == 0x50, invalid_offset);

void GPIO_Init() {
	// Set PS[16] to power on all quadrants of GPIO (enable clk)
	// PCR_ClearPowerDown(16, 0b1111);

	// Start GIO
	gpioREG->GCR0 = 1;

	// For interrupts later
	gpioREG->ENACLR = 0xFFU;
	gpioREG->LVLCLR = 0xFFU;
}

// How many pins are in each set 'A' and 'B'
#define PINS_PER_SET 8

// Returns whether the pin falls into the 'A' set of pins.
#define IS_PIN_A(pin) (pin < PINS_PER_SET)
#define PIN_OFFSET(pin) (IS_PIN_A(pin) ? pin : pin - PINS_PER_SET)
#define DIR_OFFSET(pin) (IS_PIN_A(pin) ? &gpioREG->DIRA : &gpioREG->DIRB)
#define PULLDIS_OFFSET(pin) (IS_PIN_A(pin) ? &gpioREG->PULDISA : &gpioREG->PULDISB)
#define PULLSEL_OFFSET(pin) (IS_PIN_A(pin) ? &gpioREG->PULSELA : &gpioREG->PULSELB)
#define DRAIN_OFFSET(pin) (IS_PIN_A(pin) ? &gpioREG->PDRA : &gpioREG->PDRB)
#define DSET_OFFSET(pin) (IS_PIN_A(pin) ? &gpioREG->DSETA : &gpioREG->DSETB)
#define DCLR_OFFSET(pin) (IS_PIN_A(pin) ? &gpioREG->DCLRA : &gpioREG->DCLRB)

static uint32_t currentDirectionStateA = 0;
static uint32_t currentDirectionStateB = 0;

void GPIO_SetDirection(gpio_pin_t pin, gpio_dir_t dir) {
	uint32_t* state = IS_PIN_A(pin) ? &currentDirectionStateA : &currentDirectionStateB;

	if (dir == GPIO_DIR_OUTPUT) {
		*state |= (1 << PIN_OFFSET(pin));
	} else {
		*state &= ~(1 << PIN_OFFSET(pin));
	}

	*DIR_OFFSET(pin) = *state;
}

static uint32_t currentOpenDrainStateA = 0;
static uint32_t currentOpenDrainStateB = 0;

void GPIO_SetOpenDrain(gpio_pin_t pin, bool isOpen) {
	uint32_t* state = IS_PIN_A(pin) ? &currentOpenDrainStateA : &currentOpenDrainStateB;

	if (isOpen) {
		*state |= (1 << PIN_OFFSET(pin));
	} else {
		*state &= ~(1 << PIN_OFFSET(pin));
	}

	*DRAIN_OFFSET(pin) = *state;
}

void GPIO_SetPullDisabled(gpio_pin_t pin, bool isDisabled) {
	if (isDisabled) {
		*PULLDIS_OFFSET(pin) = 1 << PIN_OFFSET(pin);
	} else {
		*PULLDIS_OFFSET(pin) = 0 << PIN_OFFSET(pin);
	}
}

void GPIO_SetHigh(gpio_pin_t pin, bool isHigh) {
	if (isHigh) {
		*DSET_OFFSET(pin) = 1 << PIN_OFFSET(pin);
	} else {
		*DCLR_OFFSET(pin) = 1 << PIN_OFFSET(pin);
	}
}
