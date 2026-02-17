// Refer to page 1623 of TRM for SCI Control Registers

#include "sci.h"
#include "iomm.h"

#include <math.h>
#include <stdbool.h>

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

static void initReg(sci_register_t* reg, sci_loopback_t loopback) {
	// Bring out of reset
	reg->GCR0 = 0;
	reg->GCR0 = 1;

	// Disable all interrupts
	reg->CLEARINT = 0xFFFFFFFFU;
	reg->CLEARINTLVL = 0xFFFFFFFFU;

	/* clang-format off */
	reg->GCR1 =
		SCIGCR1_TXENA |
		SCIGCR1_RXENA |
		SCIGCR1_CLOCK |
		SCIGCR1_STOPBITS(2) |
		SCIGCR1_PARITY_DISABLED |
		SCIGCR1_ASYNC;
	/* clang-format on */

	// Set baudrate
	reg->BRS = 715U;

	// Set length
	reg->FORMAT = 8U - 1U; // 8 bits

	SCI_SetLoopback(reg, loopback);

	// todo: allow users to configure this
	// VCLK = 8MHz
	// SCICLK = VCLK / (P + 1 + M/16)
	// Target SCICLK = 115200
	// M = 5, P = 3
	// = ~ 115900 (small enough error for 115200 baud)
	// setBaudRatePrescalers(3, 5);

	// Enable SCI pins for tx and rx instead of GIO
	reg->PIO0 = (1U << 2U) | (1U << 1U); // tx and rx pin functional mode
	reg->PIO3 = 0U; // Set SCI pins default output value
	reg->PIO1 = 0U; // Set SCI pins output direction
	reg->PIO6 = 0U; // Set SCI pins open drain enable
	reg->PIO7 = 0U; // Set SCI pins pullup/pulldown enable
	reg->PIO8 = (1U << 2U) | (1U << 1U); // Set SCI pins pullup/pulldown select

	reg->GCR1 |= SCIGCR1_SWNRST;
}

#define PINMUX_PIN_38_SHIFT 16U
#define PINMUX_PIN_39_SHIFT 0U

#define PINMUX_PIN_38_SCIRX (0x2U << PINMUX_PIN_38_SHIFT)
#define PINMUX_PIN_39_SCITX (0x2U << PINMUX_PIN_39_SHIFT)

void SCI_Init(sci_config_t* config) {
	IOMM_UnlockPinMMR();
	iommREG->PINMMR[7] = (1 << 17); // Set N2HET1[06] to SCIRX
	iommREG->PINMMR[8] = (1 << 1);	// Set N2HET1[13] to SCITX
	IOMM_LockPinMMR();

	initReg(sciREG, config->sciLoopback);
	initReg(scilinREG, config->scilinLoopback);
}

uint32_t SCI_GetFlags(sci_register_t* reg) {
	return reg->FLR;
}

// Get the raw flags from SCI. Mostly meant for internal use.
#define SCI_FLAGS_RXRDY_MASK (1U << 9U)
#define SCI_FLAGS_TXRDY_MASK (1U << 8U)
#define SCI_FLAGS_BUSY_MASK (1U << 3U)
#define SCI_FLAGS_IDLE_MASK (1U << 2U)
#define SCI_FLAGS_WAKEUP_MASK (1U << 1U)
#define SCI_FLAGS_BRKDT_MASK (1U << 0U)

static inline bool isReceiveReady(sci_register_t* reg) {
	return (reg->FLR & SCI_FLAGS_RXRDY_MASK) != 0;
}

static inline bool isTransmitReady(sci_register_t* reg) {
	return (reg->FLR & SCI_FLAGS_TXRDY_MASK) != 0;
}

static void writeByte(sci_register_t* reg, uint8_t data) {
	reg->TD = data;
}

static uint8_t readByte(sci_register_t* reg) {
	return (uint8_t)(reg->RD & 0xFFU);
}

void SCI_SyncTransmitByte(sci_register_t* reg, uint8_t data) {
	while (!isTransmitReady(reg)) {
		// Wait
	}

	writeByte(reg, data);
}

/// - Analog: Routes SCITX through SCIRX and uses that
/// - Digital: Entirely bypasses the pins and routes internally
void SCI_SetLoopback(sci_register_t* reg, sci_loopback_t mode) {
	if (mode == SCI_LOOPBACK_DISABLE) {
		reg->IODFTCTRL = 0x00000500U;
	} else if (mode == SCI_LOOPBACK_ANALOG) {
		reg->IODFTCTRL = (0xA00U | 2U);
	} else if (mode == SCI_LOOPBACK_DIGITAL) {
		reg->IODFTCTRL = 0xA00U;
	}
}

uint8_t SCI_SyncReceiveByte(sci_register_t* reg) {
	while (!isReceiveReady(reg)) {
		// Wait
	}

	return readByte(reg);
}
