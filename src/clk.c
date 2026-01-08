#include "clk.h"

#include "util.h"
#include <stdbool.h>

// Clock sources information can be found at page 120 of TRM
#define CLK_CS_OSCIN 0
#define CLK_CS_PLL1 1
#define CLK_CS_EXTCLKIN 3
#define CLK_CS_LOWFREQ 4
#define CLK_CS_HIGHFREQ 5
#define CLK_CS_PLL2 6
#define CLK_CS_EXTCLKIN2 7

#define CLK_BASE 0xFFFFE100
#define CLK_CSDIS_OFFSET 0x30
#define CLK_PLLCTL1_OFFSET 0x70
#define CLK_PLLCTL2_OFFSET 0x74
#define CLK_GHVSRC_OFFSET 0x48 // GCLK/HCLK/VCLK/VCLK2
#define CLK_RCLKSRC_OFFSET 0x50 // RTI CLK

#define CLK_GHVSRC_SRC(s) s
#define CLK_RCLKSRC_SRC(s) s

// Default clock domains located on TRM page 121
// GCLK = OSCIN
// HCLK = OSCIN (in phase with GCLK)
// VCLK = HCLK / N (where N is 2 by default, see page 123 of TRM)

// Info found on page 1520 of TRM.
// SCICLK = (VCLK) / (P + 1 + (M/16))
// SCICLK = 8MHz / (P + 1 + (M/16))

// Discovered according to schematic
// 16MHz
#define LAUNCHXL_OSCIN_HZ 16000000U

void CLK_Init() {
	// Ensure default clock source for vclk/hclk/gclk is just OSCIN
	// No PLL
	set(uint32_t, CLK_BASE + CLK_GHVSRC_OFFSET, CLK_GHVSRC_SRC(CLK_CS_OSCIN));

	// Ensure RTI is set to VCLK
	set(uint32_t, CLK_BASE + CLK_RCLKSRC_OFFSET, CLK_RCLKSRC_SRC(9));
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
