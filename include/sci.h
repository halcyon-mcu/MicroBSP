#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "util.h"

typedef enum { /* clang-format off */
	SCI_LOOPBACK_DISABLE = 0,
	SCI_LOOPBACK_ANALOG = 1,
	SCI_LOOPBACK_DIGITAL = 2
} sci_loopback_t; /* clang-format on */

// Get the raw flags from SCI. Mostly meant for internal use.
#define SCI_FLAGS_RXRDY_MASK (1U << 9U)
#define SCI_FLAGS_TXRDY_MASK (1U << 8U)
#define SCI_FLAGS_BUSY_MASK (1U << 3U)
#define SCI_FLAGS_IDLE_MASK (1U << 2U)
#define SCI_FLAGS_WAKEUP_MASK (1U << 1U)
#define SCI_FLAGS_BRKDT_MASK (1U << 0U)

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
	volatile uint32_t _RESERVED[12U];
	volatile uint32_t IODFTCTRL;
} sci_register_t;

STATIC_ASSERT(offsetof(sci_register_t, GCR0) == 0x00, sci_register_t_size_mismatch);
STATIC_ASSERT(offsetof(sci_register_t, PIO7) == 0x58, sci_register_t_size_mismatch);
STATIC_ASSERT(offsetof(sci_register_t, FLR) == 0x1C, sci_register_t_size_mismatch);
STATIC_ASSERT(offsetof(sci_register_t, IODFTCTRL) == 0x90, sci_register_t_size_mismatch);

extern sci_register_t* const sciREG;
extern sci_register_t* const scilinREG;

/**
 * SCI Initialization function. This must be called a single time upon reset.
 * Initializes SCI in SCI mode.
 *
 * # SAFETY
 * This assumes that SYS_Init has been called beforehand.
 */
void SCI_Init(sci_register_t* sci);
uint32_t SCI_GetFlags(sci_register_t* sci);
void SCI_SyncTransmitByte(sci_register_t* sci, uint8_t data);
uint8_t SCI_SyncReceiveByte(sci_register_t* sci);
void SCI_SetLoopback(sci_register_t* sci, sci_loopback_t mode);
void SCI_SetBaudRate(sci_register_t* sci, uint32_t rate);

#ifdef __cplusplus
}
#endif
