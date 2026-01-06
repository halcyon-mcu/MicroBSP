// Refer to page 1623 of TRM for SCI Control Registers

#include "sci.h"
#include "pcr.h"
#include "util.h"

#include <stdbool.h>

#define SCI_BASE 0xFFF7E500

#define SCI_GCR0_OFFSET 0x00
#define SCI_GCR1_OFFSET 0x04
#define SCI_FLR_OFFSET 0x1C
#define SCI_FORMAT_OFFSET 0x28
#define SCI_BRS_OFFSET 0x2C
#define SCI_RD_OFFSET 0x34
#define SCI_TD_OFFSET 0x38
#define SCI_PIO0_OFFSET 0x3C
#define SCI_PIO1_OFFSET 0x40
#define SCI_PIO2_OFFSET 0x44
#define SCI_PIO3_OFFSET 0x48
#define SCI_PIO4_OFFSET 0x4C
#define SCI_PIO5_OFFSET 0x50
#define SCI_PIO6_OFFSET 0x54
#define SCI_PIO7_OFFSET 0x58

#define SCIGCR1_TXENA (1 << 25)
#define SCIGCR1_RXENA (1 << 24)
#define SCIGCR1_CONT (1 << 17)
#define SCIGCR1_SWNRST (1 << 7)
#define SCIGCR1_CLOCK (1 << 5)
#define SCIGCR1_ASYNC (1 << 1)

static void setBaudRatePrescalers(uint32_t p, uint32_t m) {
	set(uint32_t, SCI_BASE + SCI_BRS_OFFSET, (m & 0xF << 24) | (p & 0xFFFFFF));
}

void SCI_Init() {
	// Set PS[6] to power on all quadrants of SCI (enable clk)
	PCR_ClearPowerDown(6, 0b1111);

	set(uint32_t, SCI_BASE + SCI_GCR0_OFFSET, 1);

	// Reset SCI before configuration
	set(uint32_t, SCI_BASE + SCI_GCR1_OFFSET, 0);

	set(uint32_t, SCI_BASE + SCI_GCR1_OFFSET, SCIGCR1_TXENA | SCIGCR1_RXENA | SCIGCR1_CLOCK | SCIGCR1_ASYNC | SCIGCR1_CONT);

	// todo: allow users to configure this
	// VCLK = 8MHz
	// SCICLK = VCLK / (P + 1 + M/16)
	// Target SCICLK = 115200
	// M = 5, P = 3
	// = ~ 115900 (small enough error for 115200 baud)
	setBaudRatePrescalers(3, 5);

	set(uint32_t, SCI_BASE + SCI_GCR1_OFFSET, SCIGCR1_SWNRST);
}

unsigned int SCI_GetFlags() {
	return get(uint32_t, SCI_BASE + SCI_FLR_OFFSET);
}

// Get the raw flags from SCI. Mostly meant for internal use.
#define SCI_FLAGS_RXRDY_MASK (1 << 9)
#define SCI_FLAGS_TXRDY_MASK (1 << 8)
#define SCI_FLAGS_BUSY_MASK (1 << 3)
#define SCI_FLAGS_IDLE_MASK (1 << 2)
#define SCI_FLAGS_WAKEUP_MASK (1 << 1)
#define SCI_FLAGS_BRKDT_MASK (1 << 0)

static bool isReceiveReady() {
	return SCI_GetFlags() & SCI_FLAGS_RXRDY_MASK;
}

static bool isTransmitReady() {
	return SCI_GetFlags() & SCI_FLAGS_TXRDY_MASK;
}

static void writeByte(uint8_t data) {
	set(uint8_t, SCI_BASE + SCI_TD_OFFSET, data);
}

static uint8_t readByte() {
	return get(uint8_t, SCI_BASE + SCI_RD_OFFSET);
}

void SCI_SyncTransmitByte(uint8_t data) {
	while (!isTransmitReady()) {
		// Wait
	}

	writeByte(data);
}

uint8_t SCI_SyncReceiveByte() {
	while (!isReceiveReady()) {
		// Wait
	}

	return readByte();
}
