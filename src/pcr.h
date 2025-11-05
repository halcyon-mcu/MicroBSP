#pragma once

#define PCR_BASE 0xFFFFE000

#define PCR_PSPWRDWNCLR0_OFFSET 0xA0
#define PCR_PSPWRDWNCLR1_OFFSET 0xA4
#define PCR_PSPWRDWNCLR2_OFFSET 0xA8
#define PCR_PSPWRDWNCLR3_OFFSET 0xAC

void PCR_ClearPowerDown(unsigned int ps, unsigned int quad);
