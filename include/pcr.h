#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void PCR_ClearPowerDown(unsigned int ps, unsigned int quad);
void PCR_SetPowerDown(unsigned int ps, unsigned int quad);

#ifdef __cplusplus
}
#endif
