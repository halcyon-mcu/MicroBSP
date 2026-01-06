/**
 * SCI example for MicroBSP
 */

#include "sci.h"
#include "clk.h"
#include "gpio.h"
#include "pcr.h"
#include "sys1.h"

int main() {
	SYS1_Init();
	GPIO_Init();
	SCI_Init();
	CLK_Init();

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);
	GPIO_SetHigh(GPIOB_1, true);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	uint32_t counter = 0;
	while (true) {
		SCI_SyncTransmitByte(0xDE);
		SCI_SyncTransmitByte(0xAD);
		SCI_SyncTransmitByte(0xBE);
		SCI_SyncTransmitByte(0xEF);
		// uint8_t _ = SCI_SyncReceiveByte();
		counter++;
	}

	return 0;
}
