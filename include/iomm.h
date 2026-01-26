#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	volatile uint32_t REVISION_REG;			  // 0h
	volatile uint32_t RESERVED1[7];			  // 4h-1Ch
	volatile uint32_t ENDIAN_REG;			  // 20h
	volatile uint32_t RESERVED2[5];			  // 24h-34h
	volatile uint32_t KICK_REG0;			  // 38h
	volatile uint32_t KICK_REG1;			  // 3Ch
	volatile uint32_t RESERVED3[40];		  // 40h-DCh
	volatile uint32_t ERR_RAW_STATUS_REG;	  // E0h
	volatile uint32_t ERR_ENABLED_STATUS_REG; // E4h
	volatile uint32_t ERR_ENABLE_REG;		  // E8h
	volatile uint32_t ERR_ENABLE_CLR_REG;	  // ECh
	volatile uint32_t RESERVED4[1];			  // F0h
	volatile uint32_t FAULT_ADDRESS_REG;	  // F4h
	volatile uint32_t FAULT_STATUS_REG;		  // F8h
	volatile uint32_t FAULT_CLEAR_REG;		  // FCh
	volatile uint32_t RESERVED5[644];		  // 100h-B0Ch
	volatile uint32_t PINMMR[48];			  // B10h-BCCh
} iomm_register_t;

STATIC_ASSERT(offsetof(iomm_register_t, REVISION_REG) == 0x00, iomm_register_t_size_mismatch);
STATIC_ASSERT(offsetof(iomm_register_t, ENDIAN_REG) == 0x20, iomm_register_t_size_mismatch);

extern iomm_register_t* const iommREG;

void IOMM_UnlockPinMMR();
void IOMM_LockPinMMR();

#ifdef __cplusplus
}
#endif
