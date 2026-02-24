/**
 * Run the generic test suite with microbsp as the backend.
 */

#include "gpio.h"
#include "sci.h"
#include "testframework.h"

static sci_register_t* s_port;

void test_led_on(test_pin_t pin) {
	gpio_pin_t gpio_pin = (pin == TEST_LED_PIN_1) ? GPIOB_1 : GPIOB_2;
	GPIO_SetHigh(gpio_pin, true);
}

void test_led_off(test_pin_t pin) {
	gpio_pin_t gpio_pin = (pin == TEST_LED_PIN_1) ? GPIOB_1 : GPIOB_2;
	GPIO_SetHigh(gpio_pin, false);
}

void test_led_toggle(test_pin_t pin) {
	// No dedicated toggle in GPIO API; track state via on/off calls.
	// Read current output by using a static flag per pin.
	static bool state1 = false;
	static bool state2 = false;

	if (pin == TEST_LED_PIN_1) {
		state1 = !state1;
		GPIO_SetHigh(GPIOB_1, state1);
	} else {
		state2 = !state2;
		GPIO_SetHigh(GPIOB_2, state2);
	}
}

void test_printbyte(uint8_t byte) {
	if (byte == '\n') {
		SCI_SyncTransmitByte(s_port, '\r');
	}

	SCI_SyncTransmitByte(s_port, byte);
}

void test_recvbyte(uint8_t* byte) {
	*byte = SCI_SyncReceiveByte(s_port);
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

	s_port = scilinREG;

	test_run();

	while (true) {
		// halt
	}

	return 0;
}
