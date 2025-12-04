#include "clk.h"

// UB to access this without CLK_Init first.
static clk_config_t globalConfig;

// Info found on page 1520 of TRM.
// SCICLK = (VCLK) / (P + 1 + (M/16))

void CLK_Init(clk_config_t config) {
	globalConfig = config;
}
