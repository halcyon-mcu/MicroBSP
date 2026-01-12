#pragma once

#include "util.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	volatile uint32_t FRDCNTRL;		  // 0x0
	volatile uint32_t reserved1;	  // 0x4
	volatile uint32_t FEDACTRL1;	  // 0x8
	volatile uint32_t FEDACTRL2;	  // 0xC
	volatile uint32_t FCOR_ERR_CNT;	  // 0x10
	volatile uint32_t FCOR_ERR_ADD;	  // 0x14
	volatile uint32_t FCOR_ERR_POS;	  // 0x18
	volatile uint32_t FEDACSTATUS;	  // 0x1C
	volatile uint32_t FUNC_ERR_ADD;	  // 0x20
	volatile uint32_t FEDACSDIS;	  // 0x24
	volatile uint32_t FPRIM_ADD_TAG;  // 0x28
	volatile uint32_t FDUP_ADD_TAG;	  // 0x2C
	volatile uint32_t FBPROT;		  // 0x30
	volatile uint32_t FBSE;			  // 0x34
	volatile uint32_t FBBUSY;		  // 0x38
	volatile uint32_t FBAC;			  // 0x3C
	volatile uint32_t FBFALLBACK;	  // 0x40
	volatile uint32_t FBPRDY;		  // 0x44
	volatile uint32_t FPAC1;		  // 0x48
	volatile uint32_t FPAC2;		  // 0x4C
	volatile uint32_t FMAC;			  // 0x50
	volatile uint32_t FMSTAT;		  // 0x54
	volatile uint32_t FEMU_DMSW;	  // 0x58
	volatile uint32_t FEMU_DLSW;	  // 0x5C
	volatile uint32_t FEMU_ECC;		  // 0x60
	volatile uint32_t reserved2;	  // 0x64
	volatile uint32_t FEMU_ADDR;	  // 0x68
	volatile uint32_t FDIAGCTRL;	  // 0x6C
	volatile uint32_t FRAW_DATAH;	  // 0x70
	volatile uint32_t FRAW_DATAL;	  // 0x74
	volatile uint32_t FRAW_ECC;		  // 0x78
	volatile uint32_t FPAR_OVR;		  // 0x7C
	volatile uint32_t reserved3[16];  // 0x80-0xBC
	volatile uint32_t FEDACSDIS2;	  // 0xC0
	volatile uint32_t reserved4[113]; // 0xC4-0x284
	volatile uint32_t FSM_WR_ENA;	  // 0x288
	volatile uint32_t reserved5[6];	  // 0x28C-0x2A0
	volatile uint32_t FSM_SECTOR;	  // 0x2A4
	volatile uint32_t reserved6[4];	  // 0x2A8-0x2B4
	volatile uint32_t EEPROM_CONFIG;  // 0x2B8
	volatile uint32_t reserved7[19];  // 0x2BC-0x304
	volatile uint32_t EE_CTRL1;		  // 0x308
	volatile uint32_t EE_CTRL2;		  // 0x30C
	volatile uint32_t EE_COR_ERR_CNT; // 0x310
	volatile uint32_t EE_COR_ERR_ADD; // 0x314
	volatile uint32_t EE_COR_ERR_POS; // 0x318
	volatile uint32_t EE_STATUS;	  // 0x31C
	volatile uint32_t EE_UNC_ERR_ADD; // 0x320
	volatile uint32_t reserved8[55];  // 0x324-0x3FC
	volatile uint32_t FCFG_BANK;	  // 0x400
} flash_register_t;

STATIC_ASSERT(offsetof(flash_register_t, FRDCNTRL) == 0x0, flash_register_t_size_mismatch);

extern flash_register_t* const flashREG;

void FLASH_Init();

#ifdef __cplusplus
}
#endif
