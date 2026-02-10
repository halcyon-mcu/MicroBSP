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

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);
	GPIO_SetHigh(GPIOB_1, true);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	volatile uint32_t i;
	bool high = false;
	while (true) {
		GPIO_SetHigh(GPIOB_2, high);
		high = !high;

		SCI_SyncTransmitByte('A');
		SCI_SyncTransmitByte('B');

		for (i = 0; i < 1000000; i++) {
			// yeah
		}
	}

	return 0;
}
