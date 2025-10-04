ENTRY(Reset_Handler)

_Min_Heap_Size = 0x400; /* required amount of heap */
_Min_Stack_Size = 0x400; /* required amount of stack */

MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =512K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =128K
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP (*(.bootloader_section))
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
        *(.text)         
        *(.text.*)         
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)

        KEEP(*(.init))
        KEEP(*(.fini))
        . = ALIGN(4);

        *(.rodata)        
        *(.rodata.*)        

        . = ALIGN(4);
        _etext = .;       
    } > FLASH
    
    .arrays (READONLY):
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } >FLASH

    _la_data = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;   
        *(.data)           
        *(.data*)          
        *(.RamFunc)        
        *(.RamFunc*)       
        . = ALIGN(4);
        _edata = .;   
    } > SRAM AT> FLASH


    .bss :
    {
        . = ALIGN(4);
        _sbss = .;    
        __bss_start__ = _sbss;
        
        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } > SRAM 
    
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >SRAM

    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }
}
