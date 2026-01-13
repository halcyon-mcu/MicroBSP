// Refer to page 1623 of TRM for SCI Control Registers

#include "sci.h"

#include <stdbool.h>

sci_register_t* const sciREG = (sci_register_t*)(uintptr_t)(0xFFF7E500UL);
sci_register_t* const scilinREG = (sci_register_t*)(uintptr_t)(0xFFF7E400UL);

// I'd like to use bitfield struct here but isn't safe across different compilers
#define SCIGCR1_TXENA (1U << 25U)
#define SCIGCR1_RXENA (1U << 24U)
#define SCIGCR1_CONT (1U << 17U)
#define SCIGCR1_LOOPBACK (1U << 16U)
#define SCIGCR1_SWNRST (1U << 7U)
#define SCIGCR1_CLOCK_INTERNAL (1U << 5U)
#define SCIGCR1_ASYNC (1U << 1U)

/// Set the number of stop bits (1 or 2)
#define SCIGCR1_STOPBITS(n) (((n) - 1U) << 4U)

#define SCIGCR1_PARITY_EVEN (1U << 3U)
#define SCIGCR1_PARITY_ODD (0U << 3U)

#define SCIGCR1_PARITY_ENABLED (1U << 2U)
#define SCIGCR1_PARITY_DISABLED (0U << 2U)


// void SCI_SetBaudRate(uint32_t rate) {
// 	const float vclk = 8.0e6f; // 8 MHz
// 	const uint32_t f = (sciREG->GCR1 & SCIGCR1_ASYNC) ? 16U : 1U;

// 	const float divisor = (vclk / (f * rate)) - 1.0f;
// 	const uint32_t brs = (uint32_t)(floorf(divisor + 0.5f)) & 0x00FFFFFFU;

// 	sciREG->BRS = brs;
// }

void SCI_Init(sci_register_t* sci) {
	// Bring out of reset
	sci->GCR0 = 0;
	sci->GCR0 = 1;

	// Disable all interrupts
	sci->CLEARINT = 0xFFFFFFFFU;
	sci->CLEARINTLVL = 0xFFFFFFFFU;

	/* clang-format off */
	sci->GCR1 =
		SCIGCR1_TXENA |
		SCIGCR1_RXENA |
		SCIGCR1_CLOCK_INTERNAL |
		SCIGCR1_STOPBITS(1) |
		SCIGCR1_PARITY_DISABLED |
		SCIGCR1_LOOPBACK |
		SCIGCR1_ASYNC;
	/* clang-format on */

	// Set baudrate (9600)
	sci->BRS = 715U;

	// Set length
	sci->FORMAT = 8U - 1U; // 8 bits

	// Enable SCI pins for tx and rx instead of GIO
	sci->PIO0 = (1U << 2U) | (1U << 1U); // tx and rx pin functional mode

	// Set SCI pins default output value
	// sci->PIO3 = 0U;

	// // Set SCI pins output direction
	// sci->PIO1 = 0U;

	// // Set SCI pins open drain enable
	// sci->PIO6 = 0U;

	// // Set SCI pins pullup/pulldown enable
	// sci->PIO7 = 0U;

	// // Set SCI pins pullup/pulldown select
	// sci->PIO8 = (1U << 2U) | (1U << 1U);

	sci->GCR1 |= SCIGCR1_SWNRST;
}

uint32_t SCI_GetFlags(sci_register_t* sci) {
	return sci->FLR;
}

static inline bool isReceiveReady(sci_register_t* sci) {
	return (sci->FLR & SCI_FLAGS_RXRDY_MASK) != 0;
}

static inline bool isTransmitReady(sci_register_t* sci) {
	return (sci->FLR & SCI_FLAGS_TXRDY_MASK) != 0;
}

static void writeByte(sci_register_t* sci, uint8_t data) {
	sci->TD = data;
	sci->FLR &= ~SCI_FLAGS_TXRDY_MASK;
}

static uint8_t readByte(sci_register_t* sci) {
	return (uint8_t)(sci->RD & 0xFFU);
}

void SCI_SyncTransmitByte(sci_register_t* sci, uint8_t data) {
	while (!isTransmitReady(sci)) {
		// Wait
	}

	writeByte(sci, data);
}

/// - Analog: Routes SCITX through SCIRX and uses that
/// - Digital: Entirely bypasses the pins and routes internally
void SCI_SetLoopback(sci_register_t* sci, sci_loopback_t mode) {
	if (mode == SCI_LOOPBACK_DISABLE) {
		sci->IODFTCTRL = 0x00000500U;
	} else if (mode == SCI_LOOPBACK_ANALOG) {
		sci->IODFTCTRL = (0xA00U | 2U);
	} else if (mode == SCI_LOOPBACK_DIGITAL) {
		sci->IODFTCTRL = 0xA00U;
	}
}

uint8_t SCI_SyncReceiveByte(sci_register_t* sci) {
	while (!isReceiveReady(sci)) {
		volatile uint8_t dummy = readByte(sci);
		// Wait
	}

	return readByte(sci);
}
