#include "flash.h"

flash_register_t* const flashREG = (flash_register_t*)(uintptr_t)(0xFFF87000UL);

#define FRDCNTL_ENPIPE (1U << 0U)
#define FRDCNTL_DATA_WAITS(n) ((n & 0b1111) << 8U)
#define FRDCNTL_ADDRESS_WAITS(n) ((n & 0b1) << 4U)

void FLASH_Init() {
	// Set 3 data waits as directed by datasheet page 54 for running with GCLK=PLL1 at 180Mhz.
	flashREG->FRDCNTL = FRDCNTL_ADDRESS_WAITS(1) | FRDCNTL_DATA_WAITS(3) | FRDCNTL_ENPIPE;
}
