#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include <stdint.h>

typedef struct {
	volatile uint32_t SYSPC1;		// 00h
	volatile uint32_t SYSPC2;		// 04h
	volatile uint32_t SYSPC3;		// 08h
	volatile uint32_t SYSPC4;		// 0Ch
	volatile uint32_t SYSPC5;		// 10h
	volatile uint32_t SYSPC6;		// 14h
	volatile uint32_t SYSPC7;		// 18h
	volatile uint32_t SYSPC8;		// 1Ch
	volatile uint32_t SYSPC9;		// 20h
	volatile uint32_t RESERVED1[3]; // 24h-2Ch
	volatile uint32_t CSDIS;		// 30h
	volatile uint32_t CSDISSET;		// 34h
	volatile uint32_t CSDISCLR;		// 38h
	volatile uint32_t CDDIS;		// 3Ch
	volatile uint32_t CDDISSET;		// 40h
	volatile uint32_t CDDISCLR;		// 44h
	volatile uint32_t GHVSRC;		// 48h
	volatile uint32_t VCLKASRC;		// 4Ch
	volatile uint32_t RCLKSRC;		// 50h
	volatile uint32_t CSVSTAT;		// 54h
	volatile uint32_t MSTGCR;		// 58h
	volatile uint32_t MINITGCR;		// 5Ch
	volatile uint32_t MSINENA;		// 60h
	volatile uint32_t MSTFAIL;		// 64h
	volatile uint32_t MSTCGSTAT;	// 68h
	volatile uint32_t MINISTAT;		// 6Ch
	volatile uint32_t PLLCTL1;		// 70h
	volatile uint32_t PLLCTL2;		// 74h
	volatile uint32_t SYSPC10;		// 78h
	volatile uint32_t DIEIDL;		// 7Ch
	volatile uint32_t DIEIDH;		// 80h
	volatile uint32_t RESERVED2;	// 84h
	volatile uint32_t LPOMONCTL;	// 88h
	volatile uint32_t CLKTEST;		// 8Ch
	volatile uint32_t DFTCTRLREG;	// 90h
	volatile uint32_t DFTCTRLREG2;	// 94h
	volatile uint32_t RESERVED3[2]; // 98h-9Ch
	volatile uint32_t GPREG1;		// A0h
	volatile uint32_t RESERVED4;	// A4h
	volatile uint32_t IMPFASTS;		// A8h
	volatile uint32_t IMPFTADD;		// ACh
	volatile uint32_t SSIR1;		// B0h
	volatile uint32_t SSIR2;		// B4h
	volatile uint32_t SSIR3;		// B8h
	volatile uint32_t SSIR4;		// BCh
	volatile uint32_t RAMGCR;		// C0h
	volatile uint32_t BMMCR1;		// C4h
	volatile uint32_t RESERVED5;	// C8h
	volatile uint32_t CPURSTCR;		// CCh
	volatile uint32_t CLKCNTL;		// D0h
	volatile uint32_t ECPCNTL;		// D4h
	volatile uint32_t RESERVED6;	// D8h
	volatile uint32_t DEVCR1;		// DCh
	volatile uint32_t SYSECR;		// E0h
	volatile uint32_t SYSESR;		// E4h
	volatile uint32_t SYSTASR;		// E8h
	volatile uint32_t GLBSTAT;		// ECh
	volatile uint32_t DEVID;		// F0h
	volatile uint32_t SSIVEC;		// F4h
	volatile uint32_t SSIF;			// F8h
} system1_register_t;

STATIC_ASSERT(offsetof(system1_register_t, CLKCNTL) == 0xD0, system1_register_t_size_mismatch);
STATIC_ASSERT(offsetof(system1_register_t, PLLCTL1) == 0x70, system1_register_t_size_mismatch);
STATIC_ASSERT(offsetof(system1_register_t, PLLCTL2) == 0x74, system1_register_t_size_mismatch);

extern system1_register_t* const sys1REG;

void SYS_Init();

#ifdef __cplusplus
}
#endif
