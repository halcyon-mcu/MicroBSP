#pragma once

// Refer to 1303 of TRM for initialization steps

#define GPIO_BASE 0xFFF7BC00

#define GPIO_GCR0_OFFSET 0x00
#define GPIO_DIRA_OFFSET 0x34
#define GPIO_DIRB_OFFSET 0x54

#define GPIO_PDRA_OFFSET 0x48
#define GPIO_PDRB_OFFSET 0x68

#define GPIO_DSETA_OFFSET 0x40
#define GPIO_DSETB_OFFSET 0x60

#define GPIO_PULDISA_OFFSET 0x4C
#define GPIO_PULDISB_OFFSET 0x6C

void GPIO_Init();
void GPIO_SetDirection();
void GPIO_SetPulseDisabled();
void GPIO_SetOpenDrain();
