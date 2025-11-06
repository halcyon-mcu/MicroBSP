#include "gpio.h"
#include "sys1.h"
#include "sci.h"

int main() {
  SYS1_Init();
  GPIO_Init();
  SCI_Init();

  // Example: Set GPIOB[2] to high
  // This will light up User LED B
  GPIO_SetDirection(9, GPIO_DIR_OUTPUT);
  GPIO_SetOpenDrain(9, false);
  GPIO_SetHigh(9, true);

  uint8_t byte = SCI_SyncReceiveByte();

  return 0;
}
