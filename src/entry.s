.section .vectors
.word Reset_Handler

.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    ldr sp, =end_of_stack /* Set up stack pointer */

    /* Copy .data from flash to RAM */
    ldr r0, =start_of_data
    ldr r1, =start_of_data_in_flash
    ldr r2, =end_of_data
    sub r2, r2, r0
    bl memcpy

    /* Zero .bss */
    ldr r0, =start_of_bss
    ldr r1, =end_of_bss
    sub r1, r1, r0
    bl memzero

    bl main
    b . /* Infinite loop to prevent falling through */
