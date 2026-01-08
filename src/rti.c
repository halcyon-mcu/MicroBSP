#include "rti.h"

#include "util.h"

#define RTI_BASE 0xFFFFFC00

#define RTI_GCNTRL_OFFSET 0x0
#define RTI_TBCNTRL_OFFSET 0x4
#define RTI_CACNTRL_OFFSET 0x8
#define RTI_COMPCNTRL_OFFSET 0xC

#define RTI_FRC0_OFFSET 0x10
#define RTI_UC0_OFFSET 0x14
#define RTI_CPUC0_OFFSET 0x18
#define RTI_CAFRC0_OFFSET 0x1C
#define RTI_CAUC0_OFFSET 0x20
#define RTI_COMP0_OFFSET 0x50
#define RTI_UDCP0_OFFSET 0x54

#define RTI_FRC1_OFFSET 0x24
#define RTI_UC1_OFFSET 0x28
#define RTI_CPUC1_OFFSET 0x2C
#define RTI_CAFRC1_OFFSET 0x30
#define RTI_CAUC1_OFFSET 0x34
#define RTI_COMP1_OFFSET 0x58
#define RTI_UDCP1_OFFSET 0x5C

#define RTI_GCNTRL_CNT1EN (1 << 1)
#define RTI_GCNTRL_CNT0EN (1 << 0)

#define RTI_COMPSEL0_FRC0 (0 << 0)
#define RTI_COMPSEL0_FRC1 (1 << 0)

#define RTI_COMPSEL1_FRC0 (0 << 4)
#define RTI_COMPSEL1_FRC1 (1 << 4)

#define RTI_COMPSEL2_FRC0 (0 << 8)
#define RTI_COMPSEL2_FRC1 (1 << 8)

#define RTI_COMPSEL3_FRC0 (0 << 12)
#define RTI_COMPSEL3_FRC1 (1 << 12)

void RTI_Init() {
	// Enable counter 0
	set(uint32_t, RTI_BASE + RTI_GCNTRL_OFFSET, RTI_GCNTRL_CNT0EN);

	// Set initial target value to 1000
	set(uint32_t, RTI_BASE + RTI_COMP0_OFFSET, 1000);

	// Set subsequent target value to 1000 (keep repeating)
	set(uint32_t, RTI_BASE + RTI_UDCP0_OFFSET, 1000);

	// Set comparison 0 to FRC0
	set(uint32_t, RTI_BASE + RTI_COMPCNTRL_OFFSET, RTI_COMPSEL0_FRC0);
}
