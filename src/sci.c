// Refer to page 1623 of TRM for SCI Control Registers

#include "sci.h"
#include "util.h"

#include <stdbool.h>

#define SCI_BASE 0xFFF7E500

#define SCI_GCR0_OFFSET 0x00
#define SCI_FLR_OFFSET 0x1C
#define SCI_FORMAT_OFFSET 0x28
#define SCI_BRS_OFFSET 0x2C
#define SCI_RD_OFFSET 0x34
#define SCI_TD_OFFSET 0x38

void SCI_Init() {
	setbit(uint32_t, SCI_BASE + SCI_GCR0_OFFSET, 0, 1);
}

unsigned int SCI_GetFlags() {
	return get(uint32_t, SCI_BASE + SCI_FLR_OFFSET);
}

// Get the raw flags from SCI. Mostly meant for internal use.
#define SCI_FLAGS_RXRDY_MASK 0b0000000001
#define SCI_FLAGS_TXRDY_MASK 0b000000001
#define SCI_FLAGS_BUSY_MASK 0b0001
#define SCI_FLAGS_IDLE_MASK 0b001
#define SCI_FLAGS_WAKEUP_MASK 0b01
#define SCI_FLAGS_BRKDT_MASK 0b1

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

void SCI_SetBaudRate(uint32_t rate) {
	set(uint32_t, SCI_BASE + SCI_BRS_OFFSET, rate);
}
