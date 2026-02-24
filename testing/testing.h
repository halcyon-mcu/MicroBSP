#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
	TEST_OK = 0,
	// Fail and stop all tests from running
	TEST_PANIC = 1,
	TEST_FAIL = 2,
} test_result_t;

typedef enum {
	TEST_PIN_1,
	TEST_PIN_2,
} test_pin_t;

typedef test_result_t (*test_func_t)();

// These need to be implemented by the backend

void test_led_on(test_pin_t pin);
void test_led_off(test_pin_t pin);
void test_led_toggle(test_pin_t pin);

void test_printbyte(uint8_t byte);
void test_recvbyte(uint8_t* byte);

// These are base functions

inline void test_recvbytes(uint8_t* buffer, uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		test_recvbyte(&buffer[i]);
	}
}

inline void test_print(char* str) {
	while (*str) {
		test_printbyte(*str);
		str++;
	}
}

inline bool test_prompt_yn(char* prompt) {
	test_print(prompt);
	test_print(" (y/n)\n");

	while (true) {
		uint8_t byte;
		test_recvbyte(&byte);

		if (byte == 'y' || byte == 'Y') {
			return true;
		} else if (byte == 'n' || byte == 'N') {
			return false;
		}
	}
}

inline void test_it(char* name, test_func_t test_func) {
	test_print("Running test: ");
	test_print(name);
	test_print("\n");

	test_result_t result = test_func();
	switch (result) {
	case TEST_OK:
		test_print("Test passed\n");
		break;
	case TEST_FAIL:
		test_print("Test failed\n");
		break;
	case TEST_PANIC:
		test_print("Test failed with panic\n");
		while (true) {
		}
	}
}

int test_run();
