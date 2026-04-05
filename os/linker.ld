ENTRY(_start)
SECTIONS
{
    /* Secteur 1 : bootloader */
    . = 0x7C00;
    .boot : { 
        boot.o(.text) 
    }

    /* Signature boot */
    . = 0x7C00 + 510;
    .sig : { SHORT(0xAA55); }

    /* Secteur 2 : kernel */
    . = ALIGN(512); 

    .kernel : AT(ADDR(.kernel)) {
        *(.text)
        *(.rodata)
        *(.data)
        *(.bss)
    }

    /* Align fin */
    . = ALIGN(512);

    /* FIX CRITIQUE */
    /DISCARD/ :
    {
        *(.eh_frame)
        *(.comment)
    }
}
