// Refer to page 1623 of TRM for SCI Control Registers
#pragma once

#include <stdint.h>

#define SCI_BASE 0xFFF7E500

#define SCI_GCR0_OFFSET 0x00
#define SCI_FLR_OFFSET 0x1C
#define SCI_FORMAT_OFFSET 0x28
#define SCI_BRS_OFFSET 0x2C
#define SCI_RD_OFFSET 0x34
#define SCI_TD_OFFSET 0x38

void SCI_Init();

// Get the raw flags from SCI. Mostly meant for internal use.
#define SCI_FLAGS_RXRDY_MASK  0b0000000001
#define SCI_FLAGS_TXRDY_MASK  0b000000001
#define SCI_FLAGS_BUSY_MASK   0b0001
#define SCI_FLAGS_IDLE_MASK   0b001
#define SCI_FLAGS_WAKEUP_MASK 0b01
#define SCI_FLAGS_BRKDT_MASK  0b1
unsigned int SCI_GetFlags();


void SCI_SyncTransmitByte(uint8_t data);
uint8_t SCI_SyncReceiveByte();

void SCI_SetBaudRate(uint32_t rate);
