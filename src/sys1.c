#include "sys1.h"

#include "util.h"
#include <stdint.h>

#define SYS1_BASE 0xFFFFFF00
#define SYS1_CLKCNTL_OFFSET 0xD0

void SYS1_Init() {
	// Set peripheral enable bit: See page 176 of TRM
	setbit(uint32_t, SYS1_BASE + SYS1_CLKCNTL_OFFSET, 8, 1);
}
