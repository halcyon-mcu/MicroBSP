#include "sys1.h"

#include <stdint.h>
#include "util.h"

void SYS1_Init() {
  // Set peripheral enable bit: See page 176 of TRM
  setbit(uint32_t, SYS1_BASE + SYS1_CLKCNTL_OFFSET, 8, 1);
}
