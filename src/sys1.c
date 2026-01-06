#include "sys1.h"

#include "util.h"
#include <stdint.h>

#define SYS1_BASE 0xFFFFFF00
#define SYS1_CLKCNTL_OFFSET 0xD0
#define SYS1_PLLCTL1_OFFSET 0x70
#define SYS1_PLLCTL2_OFFSET 0x74

#define SYS1CLKCNTL_PENA (1 << 8)
#define SYS1CLKCNTL_VCLKR(r) ((r & 0b1111) << 16)
#define SYS1CLKCNTL_VCLK2R(r) ((r & 0b1111) << 24)

void SYS1_Init() {
	// Set peripheral enable bit: See page 176 of TRM
	set(uint32_t, SYS1_BASE + SYS1_CLKCNTL_OFFSET, SYS1CLKCNTL_PENA);

	// Enable peripherals and set VCLK = VCLK2 = HCLK / 2
	// set(uint32_t, SYS1_BASE + SYS1_CLKCNTL_OFFSET, SYS1CLKCNTL_PENA | SYS1CLKCNTL_VCLKR(1) | SYS1CLKCNTL_VCLK2R(1));
}
