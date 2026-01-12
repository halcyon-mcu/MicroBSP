/**
 * Blink example for MicroBSP.
 * Expected behavior:
 * - GIOB_1 pin is activated. (Right side of the board by the buttons)
 * - GIOB_2 pin blinks at an arbitrary rate spinlocking (~1s)
 */

#include "gpio.h"
#include "sys.h"

int main() {
	SYS_Init();
	GPIO_Init();

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);
	GPIO_SetHigh(GPIOB_1, true);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	uint32_t counter = 0;
	bool toggle = false;
	while (true) {
		counter++;
		if (counter % 1000000 == 0) {
			GPIO_SetHigh(GPIOB_2, toggle);
			toggle = !toggle;
			counter = 0;
		}
	}

	return 0;
}
