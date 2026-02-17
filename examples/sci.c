/**
 * SCI example for MicroBSP
 */

#include "sci.h"
#include "clk.h"
#include "gpio.h"
#include "pcr.h"

int main() {
	GPIO_Init();
	SCI_Init(&(sci_config_t){.sciLoopback = SCI_LOOPBACK_ANALOG, .scilinLoopback = SCI_LOOPBACK_DISABLE});

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	volatile uint32_t i;
	bool high = false;
	while (true) {
		GPIO_SetHigh(GPIOB_2, high);
		high = !high;

		SCI_SyncTransmitByte(sciREG, 'A');

		char c = sciREG->RD;
		if (c == 'A') {
			GPIO_SetHigh(GPIOB_1, true);
		}

		for (i = 0; i < 1000000; i++) {
			// yeah
		}
	}

	return 0;
}
