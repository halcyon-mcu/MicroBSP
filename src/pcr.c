#include "pcr.h"

#include "util.h"
#include <stdint.h>

#define QUADS_PER_REGISTER 4

void PCR_ClearPowerDown(unsigned int ps, unsigned int quad) {
  ps = ps & 0b111;
  quad = quad & 0b1111;

  set(uint32_t, PCR_BASE + PCR_PSPWRDWNCLR2_OFFSET, quad << (ps << 2));
}
