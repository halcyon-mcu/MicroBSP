// FIXME: This doesn't seem to affect anything?

#include "pcr.h"

#include <stdint.h>

pcr_register_t* const pcrREG = (pcr_register_t*)(uintptr_t)(0xFFFFE000UL);

#define QUADS_PER_REGISTER 4

/* clang-format off */
static volatile uint32_t* pwrDwnClrAddrs[4] = {
	&pcrREG->PSPWRDWNCLR0,
	&pcrREG->PSPWRDWNCLR1,
	&pcrREG->PSPWRDWNCLR2,
	&pcrREG->PSPWRDWNCLR3
}; /* clang-format on */

/* clang-format off */
static volatile uint32_t* pwrDwnSetAddrs[4] = {
	&pcrREG->PSPWRDWNSET0,
	&pcrREG->PSPWRDWNSET1,
	&pcrREG->PSPWRDWNSET2,
	&pcrREG->PSPWRDWNSET3
}; /* clang-format on */

#define PS_GROUP(ps) ((ps & 0b11111) >> 3)
#define PS_OFFSET(ps) (ps & 0b111)

void PCR_PowerUpAll() {
	pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
	pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
	pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
	pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;
}

void PCR_ClearPowerDown(unsigned int ps, unsigned int quad) {
	quad = quad & 0b1111;
	*pwrDwnClrAddrs[PS_GROUP(ps)] = quad << (PS_OFFSET(ps) << 2);
}

void PCR_SetPowerDown(unsigned int ps, unsigned int quad) {
	quad = quad & 0b1111;
	*pwrDwnSetAddrs[PS_GROUP(ps)] = quad << (PS_OFFSET(ps) << 2);
}
