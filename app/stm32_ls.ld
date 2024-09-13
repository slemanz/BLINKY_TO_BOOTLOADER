ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =480K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =96K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text) 
        *(.text.*)
        *(.init)
        *(.fini)
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
        _etext = .;
    }> FLASH

    _la_data = LOADADDR(.data);
    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        _edata = .;
    }>SRAM AT> FLASH

    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
        . = ALIGN(4);
        end = .;
    }> SRAM
}
