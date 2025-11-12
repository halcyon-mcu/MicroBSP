#include "pcr.h"

#include "util.h"
#include <stdint.h>

#define PCR_BASE 0xFFFFE000

#define PCR_PSPWRDWNCLR0_OFFSET 0xA0
#define PCR_PSPWRDWNCLR1_OFFSET 0xA4
#define PCR_PSPWRDWNCLR2_OFFSET 0xA8
#define PCR_PSPWRDWNCLR3_OFFSET 0xAC

#define QUADS_PER_REGISTER 4

/* clang-format off */
static unsigned int powerDownAddresses[4] = {
	PCR_PSPWRDWNCLR0_OFFSET,
	PCR_PSPWRDWNCLR1_OFFSET,
	PCR_PSPWRDWNCLR2_OFFSET,
	PCR_PSPWRDWNCLR3_OFFSET
}; /* clang-format on */

#define PS_GROUP(ps) ((ps & 0b11111) >> 3)
#define PS_OFFSET(ps) (ps & 0b111)

void PCR_ClearPowerDown(unsigned int ps, unsigned int quad) {
	quad = quad & 0b1111;
	set(uint32_t, PCR_BASE + powerDownAddresses[PS_GROUP(ps)], quad << (PS_OFFSET(ps) << 2));
}
