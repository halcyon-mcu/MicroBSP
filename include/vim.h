#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void VIM_Init();

/// Defined by assembly
void VIM_Disable_IRQ();

/// Defined by assembly
void VIM_Enable_IRQ();

#ifdef __cplusplus
}
#endif
