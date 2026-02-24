#include "iomm.h"

void IOMM_UnlockPinMMR() {
	iommREG->KICK_REG0 = 0x83E70B13U;
	iommREG->KICK_REG1 = 0x95A4F1E0U;
}

void IOMM_LockPinMMR() {
	iommREG->KICK_REG0 = 0x00000000U;
	iommREG->KICK_REG1 = 0x00000000U;
}
