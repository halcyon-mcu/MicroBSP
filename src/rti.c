#include "rti.h"
#include "util.h"
#include "clk.h"

#define RTI_BASE 0xFFFFFC00

#define RTI_GCNTRL_OFFSET 0x0
#define RTI_TBCNTRL_OFFSET 0x4
#define RTI_CACNTRL_OFFSET 0x8
#define RTI_COMPCNTRL_OFFSET 0xC

#define RTI_FRC0_OFFSET 0x10
#define RTI_UC0_OFFSET 0x14
#define RTI_CPUC0_OFFSET 0x18
#define RTI_CAFRC0_OFFSET 0x1C
#define RTI_CAUC0_OFFSET 0x20
#define RTI_COMP0_OFFSET 0x50
#define RTI_UDCP0_OFFSET 0x54

#define RTI_FRC1_OFFSET 0x24
#define RTI_UC1_OFFSET 0x28
#define RTI_CPUC1_OFFSET 0x2C
#define RTI_CAFRC1_OFFSET 0x30
#define RTI_CAUC1_OFFSET 0x34
#define RTI_COMP1_OFFSET 0x58
#define RTI_UDCP1_OFFSET 0x5C

#define RTI_GCNTRL_CNT1EN (1 << 1)
#define RTI_GCNTRL_CNT0EN (1 << 0)

#define RTI_COMPSEL0_FRC0 (0 << 0)
#define RTI_COMPSEL0_FRC1 (1 << 0)

#define RTI_COMPSEL1_FRC0 (0 << 4)
#define RTI_COMPSEL1_FRC1 (1 << 4)

#define RTI_COMPSEL2_FRC0 (0 << 8)
#define RTI_COMPSEL2_FRC1 (1 << 8)

#define RTI_COMPSEL3_FRC0 (0 << 12)
#define RTI_COMPSEL3_FRC1 (1 << 12)

// RTI interrupt control registers
#define RTI_INTFLAG_OFFSET 0x88
#define RTI_INTFLAG_INT0 (1 << 0)

#define RTI_CLEARINTENA_OFFSET 0x88
#define RTI_CLEARINTENA_CLEARINT0 (1 << 0)

#define RTI_SETINTENA_OFFSET 0x84
#define RTI_SETINTENA_SETINT0 (1 << 0)

// Static callback function pointer
static RTI_CallbackFunc timer_callback = 0;

void RTI_Init() {
	// Calculate compare value for 1000ms (1 second)
	// VCLK = 8MHz, so for 1 second we need 8,000,000 counts
	uint32_t compare_value = CLK_GetVClk(); // 8,000,000 for 1 second

	// Enable counter 0
	set(uint32_t, RTI_BASE + RTI_GCNTRL_OFFSET, RTI_GCNTRL_CNT0EN);

	// Set initial target value for 1000ms
	set(uint32_t, RTI_BASE + RTI_COMP0_OFFSET, compare_value);

	// Set subsequent target value to repeat every 1000ms
	set(uint32_t, RTI_BASE + RTI_UDCP0_OFFSET, compare_value);

	// Set comparison 0 to FRC0
	set(uint32_t, RTI_BASE + RTI_COMPCNTRL_OFFSET, RTI_COMPSEL0_FRC0);

	// Clear any pending interrupt flags
	set(uint32_t, RTI_BASE + RTI_INTFLAG_OFFSET, RTI_INTFLAG_INT0);
}

void RTI_SetCallback(RTI_CallbackFunc callback) {
	timer_callback = callback;
}

void RTI_StartTimer() {
	// Enable RTI compare 0 interrupt
	set(uint32_t, RTI_BASE + RTI_SETINTENA_OFFSET, RTI_SETINTENA_SETINT0);
}

void RTI_StopTimer() {
	// Disable RTI compare 0 interrupt
	set(uint32_t, RTI_BASE + RTI_CLEARINTENA_OFFSET, RTI_CLEARINTENA_CLEARINT0);
}

void RTI_CompareISR() {
	// Clear the interrupt flag
	set(uint32_t, RTI_BASE + RTI_INTFLAG_OFFSET, RTI_INTFLAG_INT0);

	// Call the registered callback if one exists
	if (timer_callback != 0) {
		timer_callback();
	}
}
