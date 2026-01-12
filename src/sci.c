// Refer to page 1623 of TRM for SCI Control Registers

#include "sci.h"
#include "pcr.h"
#include "util.h"

#include <stdbool.h>

typedef struct {
	volatile uint32_t GCR0;
	volatile uint32_t GCR1;
	volatile uint32_t GCR2;
	volatile uint32_t SETINT;
	volatile uint32_t CLEARINT;
	volatile uint32_t SETINTLVL;
	volatile uint32_t CLEARINTLVL;
	volatile uint32_t FLR;
	volatile uint32_t INTVECT0;
	volatile uint32_t INTVECT1;
	volatile uint32_t FORMAT;
	volatile uint32_t BRS;
	volatile uint32_t ED;
	volatile uint32_t RD;
	volatile uint32_t TD;
	volatile uint32_t PIO0;
	volatile uint32_t PIO1;
	volatile uint32_t PIO2;
	volatile uint32_t PIO3;
	volatile uint32_t PIO4;
	volatile uint32_t PIO5;
	volatile uint32_t PIO6;
	volatile uint32_t PIO7;
	volatile uint32_t PIO8;
	volatile uint32_t LINCOMPARE;
	volatile uint32_t LINRD0;
	volatile uint32_t LINRD1;
	volatile uint32_t LINMASK;
	volatile uint32_t LINID;
	volatile uint32_t LINTD0;
	volatile uint32_t LINTD1;
	volatile uint32_t MBRS;
	volatile uint32_t _RESERVED[4];
	volatile uint32_t IODFTCTRL;
} sci_register_t;

STATIC_ASSERT(offsetof(sci_register_t, GCR0) == 0x00, sci_register_t_size_mismatch);
STATIC_ASSERT(offsetof(sci_register_t, PIO7) == 0x58, sci_register_t_size_mismatch);
STATIC_ASSERT(offsetof(sci_register_t, FLR) == 0x1C, sci_register_t_size_mismatch);
STATIC_ASSERT(offsetof(sci_register_t, IODFTCTRL) == 0x90, sci_register_t_size_mismatch);

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

static void setBaudRatePrescalers(uint32_t p, uint32_t m) {
	sciREG->BRS = (m & 0xF << 24) | (p & 0xFFFFFF);
}

void SCI_Init() {
	// Set PS[6] to power on all quadrants of SCI (enable clk)
	PCR_ClearPowerDown(6, 0b1111);

	// Bring out of reset
	sciREG->GCR0 = 0;
	sciREG->GCR0 = 1;

	// Disable all interrupts
	sciREG->CLEARINT = 0;
	sciREG->CLEARINTLVL = 0;

	/* clang-format off */
	sciREG->GCR1 =
		SCIGCR1_TXENA |
		SCIGCR1_RXENA |
		SCIGCR1_CLOCK |
		SCIGCR1_STOPBITS(1) |
		SCIGCR1_PARITY_ODD |
		SCIGCR1_PARITY_ENABLED |
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

static bool isReceiveReady() {
	return (SCI_GetFlags() & SCI_FLAGS_RXRDY_MASK) != 0;
}

static bool isTransmitReady() {
	return (SCI_GetFlags() & SCI_FLAGS_TXRDY_MASK) != 0;
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
