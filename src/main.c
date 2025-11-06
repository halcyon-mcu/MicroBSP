#include "gpio.h"
#include "sys1.h"

int main() {
  SYS1_Init();
  GPIO_Init();

  GPIO_SetDirection(10, GPIO_DIR_OUTPUT);
  GPIO_SetOpenDrain(10, false);
  GPIO_SetHigh(10, true);

  return 0;
}
