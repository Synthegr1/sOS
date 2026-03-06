ENTRY(_start)
SECTIONS
{
    /* Secteur 1 : 0x7C00 à 0x7E00 */
    . = 0x7C00;
    .boot : { 
        boot.o(.text) 
    }

    /* On force la signature à l'octet 510 du premier secteur */
    . = 0x7C00 + 510;
    .sig : { SHORT(0xAA55); }

    /* --- Secteur 2 : Commence exactement à l'offset 512 du fichier --- */
    /* On utilise ALIGN(512) pour être sûr de commencer un nouveau secteur */
    . = ALIGN(512); 
    
    .kernel : AT(ADDR(.kernel)) {
        *(.text)
        *(.rodata)
        *(.data)
        *(.bss)
    }

    /* Optionnel : On peut aligner la fin sur 512 pour avoir un fichier propre */
    . = ALIGN(512);
}