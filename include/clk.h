#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// typedef struct {
// 	// We will have the user provide this, but on LaunchXL2 it's 16 MHz.
// 	uint32_t oscinHz;
// 	uint32_t pllMul;
// 	uint32_t pllDiv;
// 	uint32_t refClkDiv;
// 	uint32_t hClkDiv;
// 	uint32_t vClkDiv;
// } clk_config_t;

void CLK_Init();

uint32_t CLK_GetGClkHz();
uint32_t CLK_GetHClkHz();
uint32_t CLK_GetVClkHz();

#ifdef __cplusplus
}
#endif
