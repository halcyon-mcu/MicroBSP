#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * SCI Initialization function. This must be called a single time upon reset.
 * Initializes SCI in SCI mode.
 *
 * # SAFETY
 * This assumes that SYS_Init has been called beforehand.
 */
void SCI_Init();

uint32_t SCI_GetFlags();

void SCI_SyncTransmitByte(uint8_t data);
uint8_t SCI_SyncReceiveByte();

typedef enum { /* clang-format off */
	SCI_LOOPBACK_DISABLE = 0,
	SCI_LOOPBACK_ANALOG = 1,
	SCI_LOOPBACK_DIGITAL = 2
} sci_loopback_t; /* clang-format on */

void SCI_SetLoopback(sci_loopback_t mode);

// void SCI_SetBaudRate(uint32_t rate);

#ifdef __cplusplus
}
#endif
