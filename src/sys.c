#include "sys.h"

#include "pcr.h"
#include "util.h"
#include <stdint.h>

system1_register_t* const sys1REG = (system1_register_t*)(uintptr_t)(0xFFFFFF00UL);

#define SYS1CLKCNTL_PENA (1 << 8)
#define SYS1CLKCNTL_VCLKR(r) ((r & 0b1111) << 16)
#define SYS1CLKCNTL_VCLK2R(r) ((r & 0b1111) << 24)

static void initPLL() {
	// Disable PLL1 and PLL2
	sys1REG->CSDISSET = 0x00000002U | 0x00000040U;

	while ((sys1REG->CSDIS & 0x42U) != 0x42U) {
		// Wait for PLLs to disable
	}

	sys1REG->GLBSTAT = 0x301U;
}

static void initPeripherals() {
	sys1REG->CLKCNTL &= 0xFFFFFEFFU; // Disable peripherals before powering on

	PCR_PowerUpAll();

	// Enable peripherals
	sys1REG->CLKCNTL |= 0x00000100U;
}

void SYS_Init() {
	// initPLL();
	initPeripherals();
}
