ENTRY(_start) /* global _start dans le boot.asm, fonction d'amorcage */
SECTIONS {
    
    . = 0x7C00; /* Adresse du boot sector */

    .boot : { /* SECTION 'boot' */
        *(.boot_text) /* Toutes les sections .boot_text seront chargé ici */
    }

    . = 0x7C00 + 510; /* Déplacement de la signature boot de 0x7C00 à 0x7DFE */
    .sig : { SHORT(0xAA55); } /* Signature BIOS */

    . = ALIGN(512); /* Passer l'adresse mémoire au prochain multiple de 512 pour les kernel */
    
    .kernel : AT(ADDR(.kernel)) {
        *(.text) /* Code machine */
        *(.rodata) /* Données constantes */
        *(.data) /* Variables initialisés (int x = 0;)*/
        *(.bss) /* Variables non initialisés (int x;) */
    }

    . = ALIGN(512); /* Force la taille finale à être un multiple de 512 */

    /* FIX CRITIQUE */
    /DISCARD/ : /* Suppression des sections .eh_frame et .comment des fichiers .o */
    {
        *(.eh_frame) 
        *(.comment)
    }
}
