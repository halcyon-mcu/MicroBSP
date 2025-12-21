#include "clk.h"

#include <stdbool.h>

// UB to access this without CLK_Init first.
// static clk_config_t globalConfig;
// static bool isInitialized = false;

// Default clock domains located on TRM page 121
// GCLK = OSCIN
// HCLK = OSCIN (in phase with GCLK)
// VCLK = HCLK / N (where N is 2 by default, see page 123 of TRM)

// Clock Sources Table can be found on page 137 of TRM
// 0 - Oscillator
// 1 - PLL1
// 2 - Not implemented
// 3 - EXTCLKIN
// 4 - Low Freq LPO
// 5 - High Freq LPO
// 6 - PLL2
// 7 - EXTCLKIN2

// Info found on page 1520 of TRM.
// SCICLK = (VCLK) / (P + 1 + (M/16))
// SCICLK = 8MHz / (P + 1 + (M/16))

// Discovered according to schematic
#define LAUNCHXL_OSCIN_HZ 16000000U

void CLK_Init() {
	// TODO: Allow configuration with GHVSRC
}

uint32_t CLK_GetGClk() {
	return LAUNCHXL_OSCIN_HZ;
}

uint32_t CLK_GetHClk() {
	return CLK_GetGClk();
}

uint32_t CLK_GetVClk() {
	return CLK_GetHClk() / 2U;
}
