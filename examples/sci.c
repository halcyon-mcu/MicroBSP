/**
 * SCI example for MicroBSP
 */

#include "sci.h"
#include "clk.h"
#include "gpio.h"
#include "pcr.h"
#include "sys.h"

int main() {
	__auto_type sci = sciREG;

	SYS_Init();
	GPIO_Init();
	SCI_Init(sci);
	CLK_Init();

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);
	GPIO_SetHigh(GPIOB_1, true);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	SCI_SetLoopback(sci, SCI_LOOPBACK_DIGITAL);

	// while(sciREG->FLR & SCI_FLAGS_IDLE_MASK) {
	// 	// Waiting for 11-bit idle period to pass
	// }

	SCI_SyncTransmitByte(sci, 0xDE);

	uint32_t got = SCI_SyncReceiveByte(sci); // I broke here inside, and its blocking on RXRDY
	// GPIO_SetHigh(GPIOB_2, got == 0xDE);
	GPIO_SetHigh(GPIOB_2, 1);

	return 0;
}
