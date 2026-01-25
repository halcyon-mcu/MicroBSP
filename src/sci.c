// Refer to page 1623 of TRM for SCI Control Registers

#include "sci.h"
#include "pcr.h"
#include "util.h"

#include <math.h>
#include <stdbool.h>

sci_register_t* const sciREG = (sci_register_t*)(uintptr_t)(0xFFF7E500UL);

// I'd like to use bitfield struct here but isn't safe across different compilers
#define SCIGCR1_TXENA (1U << 25U)
#define SCIGCR1_RXENA (1U << 24U)
#define SCIGCR1_CONT (1U << 17U)
#define SCIGCR1_SWNRST (1U << 7U)
#define SCIGCR1_CLOCK (1U << 5U)
#define SCIGCR1_ASYNC (1U << 1U)

/// Set the number of stop bits (1 or 2)
#define SCIGCR1_STOPBITS(n) (((n) - 1U) << 4U)

#define SCIGCR1_PARITY_EVEN (1U << 3U)
#define SCIGCR1_PARITY_ODD (0U << 3U)

#define SCIGCR1_PARITY_ENABLED (1U << 2U)
#define SCIGCR1_PARITY_DISABLED (0U << 2U)

void SCI_SetBaudRate(uint32_t rate) {
	const float vclk = 8.0e6f; // 8 MHz
	const uint32_t f = (sciREG->GCR1 & SCIGCR1_ASYNC) ? 16U : 1U;

	const float divisor = (vclk / (f * rate)) - 1.0f;
	const uint32_t brs = (uint32_t)(floorf(divisor + 0.5f)) & 0x00FFFFFFU;

	sciREG->BRS = brs;
}

void SCI_Init() {
	// Set PS[6] to power on all quadrants of SCI (enable clk)
	// PCR_ClearPowerDown(6, 0b1111);

	// Bring out of reset
	sciREG->GCR0 = 0;
	sciREG->GCR0 = 1;

	// Disable all interrupts
	sciREG->CLEARINT = 0xFFFFFFFFU;
	sciREG->CLEARINTLVL = 0xFFFFFFFFU;

	/* clang-format off */
	sciREG->GCR1 =
		SCIGCR1_TXENA |
		SCIGCR1_RXENA |
		SCIGCR1_CLOCK |
		SCIGCR1_STOPBITS(1) |
		SCIGCR1_PARITY_DISABLED |
		SCIGCR1_ASYNC;
	/* clang-format on */

	// Set baudrate
	sciREG->BRS = 715U;

	// Set length
	sciREG->FORMAT = 8U - 1U; // 8 bits

	// todo: allow users to configure this
	// VCLK = 8MHz
	// SCICLK = VCLK / (P + 1 + M/16)
	// Target SCICLK = 115200
	// M = 5, P = 3
	// = ~ 115900 (small enough error for 115200 baud)
	// setBaudRatePrescalers(3, 5);

	// Enable SCI pins for tx and rx instead of GIO
	sciREG->PIO0 = (1U << 2U) | (1U << 1U); // tx and rx pin functional mode

	// Set SCI pins default output value
	sciREG->PIO3 = 0U;

	// Set SCI pins output direction
	sciREG->PIO1 = 0U;

	// Set SCI pins open drain enable
	sciREG->PIO6 = 0U;

	// Set SCI pins pullup/pulldown enable
	sciREG->PIO7 = 0U;

	// Set SCI pins pullup/pulldown select
	sciREG->PIO8 = (1U << 2U) | (1U << 1U);

	sciREG->GCR1 |= SCIGCR1_SWNRST;
}

uint32_t SCI_GetFlags() {
	return sciREG->FLR;
}

// Get the raw flags from SCI. Mostly meant for internal use.
#define SCI_FLAGS_RXRDY_MASK (1U << 9U)
#define SCI_FLAGS_TXRDY_MASK (1U << 8U)
#define SCI_FLAGS_BUSY_MASK (1U << 3U)
#define SCI_FLAGS_IDLE_MASK (1U << 2U)
#define SCI_FLAGS_WAKEUP_MASK (1U << 1U)
#define SCI_FLAGS_BRKDT_MASK (1U << 0U)

static inline bool isReceiveReady() {
	return (sciREG->FLR & SCI_FLAGS_RXRDY_MASK) != 0;
}

static inline bool isTransmitReady() {
	return (sciREG->FLR & SCI_FLAGS_TXRDY_MASK) != 0;
}

static void writeByte(uint8_t data) {
	sciREG->TD = data;
}

static uint8_t readByte() {
	return (uint8_t)(sciREG->RD & 0xFFU);
}

void SCI_SyncTransmitByte(uint8_t data) {
	while (!isTransmitReady()) {
		// Wait
	}

	writeByte(data);
}

/// - Analog: Routes SCITX through SCIRX and uses that
/// - Digital: Entirely bypasses the pins and routes internally
void SCI_SetLoopback(sci_loopback_t mode) {
	if (mode == SCI_LOOPBACK_DISABLE) {
		sciREG->IODFTCTRL = 0x00000500U;
	} else if (mode == SCI_LOOPBACK_ANALOG) {
		sciREG->IODFTCTRL = (0xA00U | 2U);
	} else if (mode == SCI_LOOPBACK_DIGITAL) {
		sciREG->IODFTCTRL = 0xA00U;
	}
}

uint8_t SCI_SyncReceiveByte() {
	while (!isReceiveReady()) {
		// Wait
	}

	return readByte();
}
