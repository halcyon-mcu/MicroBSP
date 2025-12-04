#include "clk.h"

// UB to access this without CLK_Init first.
static clk_config_t globalConfig;

// Info found on page 1520 of TRM.
// SCICLK = (VCLK) / (P + 1 + (M/16))

// Unverified:
// f_INT_CLK = f_OSCIN / (REFCLKDIV + 1)
// f_VCO_CLK = f_INT_CLK * ((PLLMUL / 256) + 1)
// f_PLL_CLK = f_VCO_CLK / (PLLDIV + 1)

void CLK_Init(clk_config_t config) {
	globalConfig = config;
}
