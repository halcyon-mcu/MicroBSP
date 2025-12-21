#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * SCI Initialization function. This must be called a single time upon reset.
 * Initializes SCI in SCI mode.
 *
 * # SAFETY
 * This assumes that SYS1_Init has been called beforehand.
 */
void SCI_Init();

unsigned int SCI_GetFlags();

void SCI_SyncTransmitByte(uint8_t data);
uint8_t SCI_SyncReceiveByte();

// void SCI_SetBaudRate(uint32_t rate);

#ifdef __cplusplus
}
#endif
