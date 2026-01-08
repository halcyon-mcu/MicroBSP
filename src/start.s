.section .vectors
.arm

.global vector_table
vector_table:
    ldr pc, Reset_Addr
    ldr pc, Undefined_Addr
    ldr pc, SVC_Addr
    ldr pc, Prefetch_Addr
    ldr pc, Abort_Addr
    nop
    ldr pc, IRQ_Addr
    ldr pc, FIQ_Addr

Reset_Addr:      .word Reset_Handler
Undefined_Addr:  .word Undefined_Handler
SVC_Addr:        .word SVC_Handler
Prefetch_Addr:   .word Prefetch_Handler
Abort_Addr:      .word Abort_Handler
IRQ_Addr:        .word IRQ_Handler
FIQ_Addr:        .word FIQ_Handler

.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    ldr sp, =end_of_stack /* Set up stack pointer */

    bl Reset_Handler_C
    b . /* Infinite loop to prevent falling through */

.global Undefined_Handler
.type Undefined_Handler, %function
Undefined_Handler:
	b . /* Infinite loop to prevent falling through */

.global SVC_Handler
.type SVC_Handler, %function
SVC_Handler:
	b . /* Infinite loop to prevent falling through */

.global Prefetch_Handler
.type Prefetch_Handler, %function
Prefetch_Handler:
	b . /* Infinite loop to prevent falling through */

.global Abort_Handler
.type Abort_Handler, %function
Abort_Handler:
	b . /* Infinite loop to prevent falling through */

.global IRQ_Handler
.type IRQ_Handler, %function
IRQ_Handler:
	b . /* Infinite loop to prevent falling through */

.global FIQ_Handler
.type FIQ_Handler, %function
FIQ_Handler:
	b . /* Infinite loop to prevent falling through */

.global VIM_Enable_IRQ
.type VIM_Enable_IRQ, %function
VIM_Enable_IRQ:
    CPSIE i

.global VIM_Disable_IRQ
.type VIM_Disable_IRQ, %function
VIM_Disable_IRQ:
    CPSID i
