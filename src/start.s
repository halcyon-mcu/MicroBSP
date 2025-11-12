.section .vectors
.word Reset_Handler

.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    ldr sp, =end_of_stack /* Set up stack pointer */

    bl Reset_Handler_C
    b . /* Infinite loop to prevent falling through */
