#include "gpio.h"
#include "sys1.h"

int main() {
  SYS1_Init();
  GPIO_Init();

  // Example: Set GPIOB[2] to high
  // This will light up User LED B
  GPIO_SetDirection(10, GPIO_DIR_OUTPUT);
  GPIO_SetOpenDrain(10, false);
  GPIO_SetHigh(10, true);

  return 0;
}
