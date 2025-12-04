#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
	uint32_t oscinHz;
	uint32_t pllMul;
	uint32_t hClkDiv;
	uint32_t vClkDiv;
} clk_config_t;

void CLK_Init(clk_config_t config);

#ifdef __cplusplus
}
#endif
