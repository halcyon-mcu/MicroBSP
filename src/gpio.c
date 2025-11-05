#include "gpio.h"

#include "pcr.h"

// SAFETY: This assumes that SYS1_Init has been called beforehand.
void GPIO_Init() {
  // Set PS[16] to power on all quadrants of GPIO (enable clk)
  PCR_ClearPowerDown(0, 0b1111);
}
