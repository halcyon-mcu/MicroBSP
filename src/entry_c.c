// Higher level Reset Handler
// This exists to avoid any more assembly code than needed.

#include <stdint.h>
#include <stddef.h>
#include "util.h"

// Linker defined addresses
extern uint32_t start_of_data;
extern uint32_t end_of_data;

extern uint32_t start_of_data_in_flash;

extern uint32_t end_of_stack;

extern uint32_t start_of_bss;
extern uint32_t end_of_bss;

// User defined entrypoint
extern int main();

void Reset_Handler_C() {
	size_t data_size = (size_t)(&end_of_data - &start_of_data);
    memcpy(&start_of_data, &start_of_data_in_flash, data_size);
    
    size_t bss_size = (size_t)(&end_of_bss - &start_of_bss);
    memset(&start_of_bss, 0, bss_size);

	main();

	// Ensure we don't go into UB
	while(1);
}
