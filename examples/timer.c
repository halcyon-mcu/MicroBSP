#include "rti.h"
#include "vim.h"
#include "clk.h"
#include "gpio.h"
#include "sys1.h"

// Example callback function that will be called every 1000ms
void my_timer_callback(void) {
    // This function is called every 1000ms (1 second)
    // Add your periodic code here

    // Example: Toggle an LED, send a heartbeat, update a display, etc.
    // For demonstration, we could increment a counter
    static volatile uint32_t callback_count = 0;
    callback_count++;

    GPIO_SetHigh(GPIOB_2, true);
}

int main(void) {
	SYS1_Init();

	// Initialize the clock system
    CLK_Init();

    // Initialize the VIM (Vectored Interrupt Manager)
    VIM_Init();

    // Initialize the RTI (Real Time Interrupt) module
    RTI_Init();

    GPIO_Init();

    // Register our callback function to be called every 1000ms
    RTI_SetCallback(my_timer_callback);

    // Start the timer - this enables the interrupt
    RTI_StartTimer();

    // Main application loop
    while (1) {
        // Your main application code runs here
        // The timer callback will interrupt this loop every 1000ms

        // Example: Sleep or do other work
        // The callback will be called automatically in the background
    }

    return 0;
}

// Alternative example showing how to change callback functions at runtime
void example_dynamic_callback_change(void) {
    // You can change the callback function at any time

    // First callback for initialization phase
    RTI_SetCallback(my_timer_callback);
    RTI_StartTimer();

    // Wait some time...

    // Later, switch to a different callback
    // RTI_SetCallback(another_callback_function);

    // Or disable the timer
    // RTI_StopTimer();

    // Or restart it later
    // RTI_StartTimer();
}
