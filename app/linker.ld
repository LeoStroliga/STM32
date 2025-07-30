/* Define memory regions. */
MEMORY
{
    rom      (rx)  : ORIGIN = 0x08000000, LENGTH = 496K
    ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

/* Enforce emission of the vector table. */
EXTERN (vector_table)

/* Define the entry point of the output file. */
ENTRY(Reset_Handler)

/* Define sections. */
SECTIONS
{
    .text : {
        KEEP (*(.bootloader_section)) 

        /* Vector table */
        *( .isr_vector )
        . = ALIGN(16);

        KEEP (*(.firmware_info))
        KEEP (*(.firmware_signature))

        *(.text*)          /* Program code */
        . = ALIGN(4);

        *(.rodata*)        /* Read-only data */
        . = ALIGN(4);
    } >rom

    /* C++ static constructors/destructors and init/fini arrays */
    .preinit_array : {
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;
    } >rom

    .init_array : {
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;
    } >rom

    .fini_array : {
        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;
    } >rom

    /* ARM exception handling sections */
    .ARM.extab : {
        *(.ARM.extab*)
    } >rom

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } >rom

    . = ALIGN(4);
    _etext = .;

    /* Non-initialized RAM section */
    .noinit (NOLOAD) : {
        *(.noinit*)
    } >ram
    . = ALIGN(4);

    /* Initialized data */
    .data : {
        _data = .;
        *(.data*)
        *(.ramtext*)
        . = ALIGN(4);
        _edata = .;
    } >ram AT >rom
    _data_loadaddr = LOADADDR(.data);

    /* BSS zero-initialized */
    .bss : {
         _sbss = .;  
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >ram

    /* Discard C++ eh_frame if unused */
    /DISCARD/ : { *(.eh_frame) }

    . = ALIGN(4);
    end = .;
}

/* Provide symbol for top of stack */
PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));
