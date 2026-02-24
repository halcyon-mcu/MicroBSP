#include "testing.h"

test_result_t test_basic_led() {
	test_led_on(TEST_PIN_1);

	if (!test_prompt_yn("led should be on")) {
		return TEST_FAIL;
	}

	test_led_off(TEST_PIN_1);

	if (!test_prompt_yn("led should be off")) {
		return TEST_PANIC;
	}

	return TEST_OK;
}

test_result_t test_arithmetic() {
	if (1 != 1) {
		return TEST_FAIL;
	}

	return TEST_OK;
}

int test_run() {
	test_it("should toggle led", test_basic_led);
	test_it("should add 1 and 1", test_arithmetic);

	return 0;
}
