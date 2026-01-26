#include "sys.h"

#include "core.h"
#include "flash.h"
#include "pcr.h"
#include <stdint.h>

system1_register_t* const sys1REG = (system1_register_t*)(uintptr_t)(0xFFFFFF00UL);

#define CLKSRC_OSCILLATOR_OFFSET 0
#define CLKSRC_PLL1_OFFSET 1
#define CLKSRC_EXTCLKIN_OFFSET 3
#define CLKSRC_LF_LPO_OFFSET 4
#define CLKSRC_HF_LPO_OFFSET 5
#define CLKSRC_PLL2_OFFSET 6
#define CLKSRC_EXTCLKIN2_OFFSET 7

#define PLLCTL_PLLMUL(r) ((((r) - 1) << 8) & 0xFFFFU)
#define PLLCTL_REFCLKDIV(r) ((((r) - 1) & 0b111111) << 16)
#define PLLCTL_RESET_ON_FAIL_ENA (1 << 23)
#define PLLCTL_PLLDIV(r) ((((r) - 1) & 0b11111) << 24)
#define PLLCTL_MASK_SLIP_ENA (1 << 29)

#define PLLCTL2_ODPLL(r) ((((r) - 1) & 0b111) << 9)

static void initPLL() {
	// Ensure PLL1 is disabled
	sys1REG->CSDISSET = 1 << CLKSRC_PLL1_OFFSET;
	while ((sys1REG->CSDIS & (1 << CLKSRC_PLL1_OFFSET)) == 0) {
		// Wait for PLL1 to disable
	}

	sys1REG->PLLCTL1 = PLLCTL_REFCLKDIV(1) | // f_intclk = f_oscin / 1
					   PLLCTL_PLLMUL(45) |	 // f_vcoclk = f_intclk * 45
					   PLLCTL_PLLDIV(2) |	 // f_pllclk = f_postodclk / 2
					   PLLCTL_RESET_ON_FAIL_ENA | PLLCTL_MASK_SLIP_ENA;

	sys1REG->PLLCTL2 = PLLCTL2_ODPLL(2); // f_postodclk = f_vcoclk / 2

	// f_pllclk = 180MHz

	// Enable PLL1
	sys1REG->CSDISCLR = 1 << CLKSRC_PLL1_OFFSET;
	while ((sys1REG->CSDIS & (1 << CLKSRC_PLL1_OFFSET)) != 0) {
		// Wait for PLL1 to enable
	}

	// Wait for PLL1 to become valid (1)
	while ((sys1REG->CSVSTAT & (1 << CLKSRC_PLL1_OFFSET)) == 0) {
		// Wait for PLL1 to lock
	}
}

#define CLKCNTL_PENA (1 << 8)
#define CLKCNTL_VCLKR(r) (((r - 1) & 0b1111) << 16)
#define CLKCNTL_VCLK2R(r) (((r - 1) & 0b1111) << 24)

static void initPeripherals() {
	sys1REG->CLKCNTL &= ~CLKCNTL_PENA;

	PCR_PowerUpAll();

	sys1REG->CLKCNTL = CLKCNTL_PENA | CLKCNTL_VCLKR(2); // VCLK = HCLK / 2
}

static void initClockMapping() {
	// Set GCLK/HCLK to use PLL1
	sys1REG->GHVSRC = ((sys1REG->GHVSRC & ~(0b1111)) | CLKSRC_PLL1_OFFSET);
}

#define MINITGCR_ENABLE 0xAU
#define MINITGCR_DISABLE 0x5U

#define MSTCGSTAT_DONE (1 << 8)

static void initMemoryUnit(uint32_t ram) {
	sys1REG->MINITGCR = MINITGCR_ENABLE;

	sys1REG->MSINENA = ram;

	// Wait for memory init to complete
	while ((sys1REG->MSTCGSTAT & MSTCGSTAT_DONE) != MSTCGSTAT_DONE) {
		// Wait
	}

	sys1REG->MINITGCR = MINITGCR_DISABLE;
}

// RAM Peripherals can be found at page 116 of TRM
// This also might help:
// https://github.com/curtfs/CURTEV-19/blob/0422dc70b692c28fe645df4ce43fa2cfa3e9c7e0/EVMS_WS/source/sys_startup.c#L378
#define MEMORY_UNIT_CPU (1 << 0)
#define MEMORY_UNIT_MIBSPI5 (1 << 12)
#define MEMORY_UNIT_MIBSPI3 (1 << 11)
#define MEMORY_UNIT_MIBSPI1 (1 << 7)
#define MEMORY_UNIT_DMA (1 << 1)
#define MEMORY_UNIT_VIM (1 << 2)
#define MEMORY_UNIT_MIBADC1 (1 << 8)
#define MEMORY_UNIT_MIBADC2 (1 << 14)
#define MEMORY_UNIT_DCAN1 (1 << 5)
#define MEMORY_UNIT_DCAN2 (1 << 6)
#define MEMORY_UNIT_DCAN3 (1 << 10)
#define MEMORY_UNIT_NTHET1 (1 << 3)
#define MEMORY_UNIT_NTHET2 (1 << 15)
#define MEMORY_UNIT_HETTU1 (1 << 4)
#define MEMORY_UNIT_HETTU2 (1 << 16)

static void initMemory() {
	initMemoryUnit(MEMORY_UNIT_CPU);

	initMemoryUnit(MEMORY_UNIT_DMA | MEMORY_UNIT_VIM | MEMORY_UNIT_DCAN1 | MEMORY_UNIT_DCAN2 | MEMORY_UNIT_MIBADC1 |
				   MEMORY_UNIT_NTHET1 | MEMORY_UNIT_HETTU1);
}

#define RAMGCR_DATAWAIT(n) (((n) & 0b1) << 0)
#define RAMGCR_ADDRWAIT(n) (((n) & 0b1) << 2)
#define RAMGCR_DFTEN(n) (((n) & 0b1111) << 16)

static void initRAM() {
	// RAM doesn't need any wait states unlike flash.
	sys1REG->RAMGCR = RAMGCR_DATAWAIT(0) | RAMGCR_ADDRWAIT(0) | RAMGCR_DFTEN(0x5);
}

static void initVIM() {
	// TODO: This
}

void SYS_Init() {
	initPLL();
	initPeripherals();
	FLASH_Init();
	initClockMapping();
	initMemory();
	CORE_EnableRamECC();
	initRAM();
	// initVIM();
}
