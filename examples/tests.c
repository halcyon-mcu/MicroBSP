/**
 * Run the generic test suite with microbsp as the backend.
 */

#include "gpio.h"
#include "sci.h"

// Wait for the user to press Enter before continuing
static void waitForEnter(sci_register_t* reg) {
	uint8_t c;
	do {
		c = SCI_SyncReceiveByte(reg);
		SCI_SyncTransmitByte(reg, c); // echo
	} while (c != '\r' && c != '\n');
}

// Returns true if user pressed y, false for n. Ignores anything else.
static bool promptYN(sci_register_t* reg) {
	while (true) {
		uint8_t c = SCI_SyncReceiveByte(reg);
		SCI_SyncTransmitByte(reg, c); // echo
		SCI_SyncTransmitByte(reg, '\n');
		if (c == 'y' || c == 'Y')
			return true;
		if (c == 'n' || c == 'N')
			return false;
	}
}

int main() {
	GPIO_Init();

	SCI_Init(&(sci_config_t){
		.sciLoopback = SCI_LOOPBACK_DISABLE,
		.scilinLoopback = SCI_LOOPBACK_DISABLE,
	});

	GPIO_SetDirection(GPIOB_1, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_1, false);

	GPIO_SetDirection(GPIOB_2, GPIO_DIR_OUTPUT);
	GPIO_SetOpenDrain(GPIOB_2, false);

	sci_register_t* port = scilinREG;

	SCI_SyncTransmitStr(port, "\033[2J\033[H");
	SCI_SyncTransmitStr(port, "This is the SCI example.\r\n");
	SCI_SyncTransmitStr(port, "Press Enter to continue...\r\n");
	waitForEnter(port);

	SCI_SyncTransmitStr(port, "\r\nThis example demonstrates basic UART communication over the SCILIN port.\r\n");
	SCI_SyncTransmitStr(port, "Characters typed are echoed back. Baud rate is 9607 (BRS=715, VCLK=110MHz).\r\n");
	SCI_SyncTransmitStr(port, "Press Enter to continue...\r\n");
	waitForEnter(port);

	while (true) {
		SCI_SyncTransmitStr(port, "\r\nFinished? [y/n]: ");
		if (promptYN(port)) {
			break;
		}
		SCI_SyncTransmitStr(port, "Ok, still here.\r\n");
	}

	SCI_SyncTransmitStr(port, "\r\nGoodbye!\r\n");

	while (true) {
		// halt
	}

	return 0;
}
