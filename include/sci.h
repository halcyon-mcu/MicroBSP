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

#define sciREG ((sci_register_t*)0xFFF7E500U)
#define scilinREG ((sci_register_t*)0xFFF7E400U)

typedef struct {
	sci_loopback_t sciLoopback;
	sci_loopback_t scilinLoopback;
} sci_config_t;

void SCI_Init(sci_config_t* config);
uint32_t SCI_GetFlags(sci_register_t* reg);
void SCI_SyncTransmitByte(sci_register_t* reg, uint8_t data);
uint8_t SCI_SyncReceiveByte(sci_register_t* reg);
void SCI_SetLoopback(sci_register_t* reg, sci_loopback_t mode);

#ifdef __cplusplus
}
#endif
