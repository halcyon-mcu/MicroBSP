/* Helpful memory aliases, also gives the linker usage hints */
MEMORY
{
    /* Program flash is 1.25mB at 0x0 (TI TRM, 110) */
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1280K

    /* On-chip RAM is 192kB at 0x08000000 (TI TRM, 105) */
    RAM (rwx)  : ORIGIN = 0x08000000, LENGTH = 192K
}

/* Assembly entrypoint */
ENTRY(Reset_Handler)

end_of_stack = ORIGIN(RAM) + LENGTH(RAM);
start_of_data_in_flash = LOADADDR(.data);

SECTIONS
{
    .text : {
        /* Important that the vectors are first as they contain refs to entrypoints */
        KEEP(*(.vectors))
        *(.text*)
    } > FLASH

    /* Use a part of flash for rodata */
    .rodata : { *(.rodata*) } > FLASH

    /* Data section in RAM, initialized from FLASH */
    .data : {
        start_of_data = .;  /* Start of .data section */
        *(.data*)
        end_of_data = .;  /* End of .data section */
    } > RAM AT > FLASH

    /* Uninitialized data section in RAM */
    .bss : {
        start_of_bss = .;
        *(.bss*)
        end_of_bss = .;
    } > RAM
}
