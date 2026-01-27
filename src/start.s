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

.equ SYS1_BASE,     0xFFFFFF00
.equ MINITGCR,      0x5C
.equ MSINENA,       0x60
.equ MSTCGSTAT,     0x68

.equ MINITGCR_ENABLE,  0xA
.equ MINITGCR_DISABLE, 0x5
.equ MEMORY_UNIT_CPU,  (1 << 0)
.equ MSTCGSTAT_DONE,   (1 << 8)

.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Initialize CPU RAM before setting up stack (for ECC) */
    ldr r0, =SYS1_BASE

    mov r1, #MINITGCR_ENABLE
    str r1, [r0, #MINITGCR]

    mov r1, #MEMORY_UNIT_CPU
    str r1, [r0, #MSINENA]

cpu_ram_init_wait:
    ldr r1, [r0, #MSTCGSTAT]
    tst r1, #MSTCGSTAT_DONE
    beq cpu_ram_init_wait

    mov r1, #MINITGCR_DISABLE
    str r1, [r0, #MINITGCR]

    /* Enable ECC now that RAM is initialized */
    mrc p15, #0x00, r0, c1, c0, #0x01
    orr r0, r0, #0x0C000000
    mcr p15, #0x00, r0, c1, c0, #0x01

    /* Now safe to set up stack pointer */
    ldr sp, =end_of_stack

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
