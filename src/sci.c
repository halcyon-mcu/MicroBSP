#include "sci.h"
#include "util.h"

#include <stdbool.h>

void SCI_Init() {
	setbit(uint32_t, SCI_BASE + SCI_GCR0_OFFSET, 0, 1);
}

unsigned int SCI_GetFlags() {
	return get(uint32_t, SCI_BASE + SCI_FLR_OFFSET);
}

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
	while (!isTransmitReady())
		;
	writeByte(data);
}

uint8_t SCI_SyncReceiveByte() {
	while (!isReceiveReady())
		;
	return readByte();
}

void SCI_SetBaudRate(uint32_t rate) {
	set(uint32_t, SCI_BASE + SCI_BRS_OFFSET, rate);
}
