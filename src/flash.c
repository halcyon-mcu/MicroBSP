#include "flash.h"

flash_register_t* const flashREG = (flash_register_t*)(uintptr_t)(0xFFF87000UL);

#define FLASH_FRDCNTRL_ENABLE_PIPE (1U << 0U)
#define FLASH_FRDCNTRL_DATA_WAITS(n) ((n & 0b1111) << 4U)
#define FLASH_FRDCNTRL_ADDRESS_WAITS(n) ((n & 0b1111) << 8U)

void FLASH_Init() {
	flashREG->FRDCNTRL = (3U << 8U)	  // 3 address wait states
						 | (1U << 4U) // 1 data wait state
						 | 1U;
}
