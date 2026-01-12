#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include <stdint.h>

typedef struct {
	volatile uint32_t PMPROTSET0;	 // 0x00
	volatile uint32_t PMPROTSET1;	 // 0x04
	volatile uint32_t reserved1[2];	 // 0x08-0x0C
	volatile uint32_t PMPROTCLR0;	 // 0x10
	volatile uint32_t PMPROTCLR1;	 // 0x14
	volatile uint32_t reserved2[2];	 // 0x18-0x1C
	volatile uint32_t PPROTSET0;	 // 0x20
	volatile uint32_t PPROTSET1;	 // 0x24
	volatile uint32_t PPROTSET2;	 // 0x28
	volatile uint32_t PPROTSET3;	 // 0x2C
	volatile uint32_t reserved3[4];	 // 0x30-0x3C
	volatile uint32_t PPROTCLR0;	 // 0x40
	volatile uint32_t PPROTCLR1;	 // 0x44
	volatile uint32_t PPROTCLR2;	 // 0x48
	volatile uint32_t PPROTCLR3;	 // 0x4C
	volatile uint32_t reserved4[4];	 // 0x50-0x5C
	volatile uint32_t PCSPWRDWNSET0; // 0x60
	volatile uint32_t PCSPWRDWNSET1; // 0x64
	volatile uint32_t reserved5[2];	 // 0x68-0x6C
	volatile uint32_t PCSPWRDWNCLR0; // 0x70
	volatile uint32_t PCSPWRDWNCLR1; // 0x74
	volatile uint32_t reserved6[2];	 // 0x78-0x7C
	volatile uint32_t PSPWRDWNSET0;	 // 0x80
	volatile uint32_t PSPWRDWNSET1;	 // 0x84
	volatile uint32_t PSPWRDWNSET2;	 // 0x88
	volatile uint32_t PSPWRDWNSET3;	 // 0x8C
	volatile uint32_t reserved7[4];	 // 0x90-0x9C
	volatile uint32_t PSPWRDWNCLR0;	 // 0xA0
	volatile uint32_t PSPWRDWNCLR1;	 // 0xA4
	volatile uint32_t PSPWRDWNCLR2;	 // 0xA8
	volatile uint32_t PSPWRDWNCLR3;	 // 0xAC
} pcr_register_t;

STATIC_ASSERT(offsetof(pcr_register_t, PMPROTSET0) == 0x00, pcr_register_t_size_mismatch);
STATIC_ASSERT(offsetof(pcr_register_t, PSPWRDWNCLR0) == 0xA0, pcr_register_t_size_mismatch);

extern pcr_register_t* const pcrREG;

void PCR_PowerUpAll();
void PCR_ClearPowerDown(unsigned int ps, unsigned int quad);
void PCR_SetPowerDown(unsigned int ps, unsigned int quad);

#ifdef __cplusplus
}
#endif
