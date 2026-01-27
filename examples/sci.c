/**
 * SCI example for MicroBSP
 */

#include "sci.h"
#include "clk.h"
#include "gpio.h"
#include "pcr.h"

int main() {
	GPIO_Init();
	SCI_Init();
	// CLK_Init();

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);
	GPIO_SetHigh(GPIOB_1, true);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	SCI_SetLoopback(SCI_LOOPBACK_DIGITAL);
	SCI_SyncTransmitByte(0xDE);

	uint32_t got = SCI_SyncReceiveByte();
	GPIO_SetHigh(GPIOB_2, got == 0xDE);

	return 0;
}
