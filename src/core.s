.global CORE_EnableRamECC
.type CORE_EnableRamECC, %function
CORE_EnableRamECC:
	mrc   p15, #0x00, r0, c1, c0, #0x01   // Read Auxiliary Control Register
	orr   r0,  r0,    #0x0C000000          // Enable B0TCM and B1TCM ECC (bits 26-27)
	mcr   p15, #0x00, r0, c1, c0, #0x01   // Write back
	bx    lr
