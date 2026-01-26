#ifndef CORE_H
#define CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enable RAM ECC for B0TCM and B1TCM
 *
 * Enables Error Correcting Code (ECC) for the tightly coupled memories
 * by setting bits 26-27 in the Auxiliary Control Register.
 */
void CORE_EnableRamECC(void);

#ifdef __cplusplus
}
#endif

#endif /* CORE_H */
