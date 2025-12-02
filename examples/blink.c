/**
 * Blink example for MicroBSP.
 * Expected behavior:
 * - GIOB_1 pin is activated. (Right side of the board by the buttons)
 */

#include "gpio.h"
#include "sci.h"
#include "sys1.h"

int main() {
	SYS1_Init();
	GPIO_Init();
	SCI_Init();

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);
	GPIO_SetHigh(GPIOB_1, true);

	// bool toggle = false;
	// while (true) {
	// 	uint8_t byte = SCI_SyncReceiveByte();
	// 	GPIO_SetHigh(GPIOB_1, toggle);
	// 	toggle = !toggle;
	// }

	return 0;
}
