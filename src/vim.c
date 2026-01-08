#include "vim.h"
#include "rti.h"
#include "util.h"
#include <stdint.h>

// Forward declaration for the interrupt service routine
void rtiCompareOISR(void);

#define VIM_BASE 0xFFFFFE00

#define VIM_IRQINDEX_OFFSET 0x0
#define VIM_FIQINDEX_OFFSET 0x4

#define VIM_REQENASET0 0x30
#define VIM_REQENASET1 0x34
#define VIM_REQENASET2 0x38
#define VIM_REQENASET3 0x3C

#define VIM_REQENACLR0 0x40
#define VIM_REQENACLR1 0x44
#define VIM_REQENACLR2 0x48
#define VIM_REQENACLR3 0x4C

// This keeps going to CHANCTRL31
// CHAN0 and CHAN1 are hard wired to INT_REQ0 and INT_REQ1
#define VIM_CHANCTRL0 0x80
#define VIM_CHANCTRL1 0x84
#define VIM_CHANCTRL2 0x88
#define VIM_CHANCTRL3 0x8C
#define VIM_CHANCTRL4 0x90
#define VIM_CHANCTRL5 0x94
#define VIM_CHANCTRL6 0x98
#define VIM_CHANCTRL7 0x9C
#define VIM_CHANCTRL8 0xA0

#define VIM_RAM_BASE 0xFFF82000

// RTI Compare 0 interrupt is typically interrupt request 2 on RM46x
#define RTI_COMPARE0_IRQ_NUM 2

void VIM_Init() {
	VIM_Enable_IRQ();
	VIM_ConfigureRTIInterrupt();
}

void VIM_ConfigureRTIInterrupt() {
	// Enable RTI Compare 0 interrupt in VIM
	// RTI_COMPARE0_IRQ_NUM (2) is in the first 32 interrupts, so use REQENASET0
	set(uint32_t, VIM_BASE + VIM_REQENASET0, (1 << RTI_COMPARE0_IRQ_NUM));
	
	// Configure channel control for RTI interrupt
	// Set as IRQ (not FIQ) and enable
	set(uint32_t, VIM_BASE + VIM_CHANCTRL2, 0x1); // Enable as IRQ
	
	// Set interrupt vector in VIM RAM
	// Each vector is 4 bytes, so RTI_COMPARE0_IRQ_NUM * 4
	set(uint32_t, VIM_RAM_BASE + (RTI_COMPARE0_IRQ_NUM * 4), (uintptr_t)&rtiCompareOISR);
}

void rtiCompareOISR() {
	// Call the RTI interrupt service routine
	RTI_CompareISR();
}
