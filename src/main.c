#include "gpio.h"
#include "sys1.h"

// #define SYS1_BASE 0xFFFFFF00
// #define SYS1_CLKCNTL_OFFSET 0xD0

// #define SYS2_BASE 0xFFFFE100

// #define PCR_BASE 0xFFFFE000
// #define PCR_PSPWRDWNCLR0_OFFSET 0xA0
// #define PCR_PSPWRDWNCLR1_OFFSET 0xA4
// #define PCR_PSPWRDWNCLR2_OFFSET 0xA8

// #define GIO_BASE 0xFFF7BC00

// #define GIOGCR0_OFFSET 0x00

// #define GIODIRA_OFFSET 0x34
// #define GIODIRB_OFFSET 0x54

// #define GIOPDRA_OFFSET 0x48
// #define GIOPDRB_OFFSET 0x68

// #define GIODSETA_OFFSET 0x40
// #define GIODSETB_OFFSET 0x60

// #define GIOPULDISA_OFFSET 0x4C
// #define GIOPULDISB_OFFSET 0x6C

int main() {
  SYS1_Init();
  GPIO_Init();
  // // Start GIO
  // setbit(uint32_t, GIO_BASE + GIOGCR0_OFFSET, 0, 1);

  // // Set GIOB[1] to be an output
  // setbit(uint32_t, GIO_BASE + GIODIRB_OFFSET, 1, 1);

  // // Disable open drain for GIOB[1]
  // setbit(uint32_t, GIO_BASE + GIOPDRB_OFFSET, 1, 0);

  // // Disable pull for GIOB[1]
  // setbit(uint32_t, GIO_BASE + GIOPULDISB_OFFSET, 1, 1);

  // // Set GIOB[1] to high
  // set(uint32_t, GIO_BASE + GIODSETB_OFFSET, 1 << 1);

  return 0;
}
