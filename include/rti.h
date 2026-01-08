#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void (*RTI_CallbackFunc)(void);

void RTI_Init();
void RTI_SetCallback(RTI_CallbackFunc callback);
void RTI_StartTimer();
void RTI_StopTimer();

/// Internal interrupt service routine (called by VIM)
void RTI_CompareISR();

#ifdef __cplusplus
}
#endif
