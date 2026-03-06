bits 16
section .text
global _start
extern main

_start:
    xor ax, ax      ; Mettre AX à 0
    mov es, ax      ; ES = 0. Donc ES:BX = 0000:7E00 = adresse 0x7E00
    mov ah, 0x02    ; Fonction BIOS "Read Sectors"
    mov al, 2       ; Nombre de secteurs à lire (1 secteur = 512 octets, on en prend 2 de plus)
    mov ch, 0       ; Cylindre 0
    mov dh, 0       ; Tête 0
    mov cl, 2       ; Secteur de départ (le secteur 1 est le bootloader, donc on commence au 2)
    mov bx, 0x7E00  ; Adresse mémoire où charger la suite (juste après le bootloader)
    int 0x13        ; Appel au BIOS

    cli                     ; 1. Désactiver les interruptions
    lgdt [gdt_descriptor]   ; 2. Charger la table des segments

    ; 3. Passer en mode protégé (bit 0 de CR0)
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; 4. Saut lointain pour vider le pipeline 16 bits
    jmp 0x08:init_32bit

bits 32
init_32bit:
    ; 5. Mettre à jour les registres de segments
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; 6. Appeler le code C
    call main

    ; 7. Bloquer si le C revient
    jmp $

; --- Table de Descripteurs Globaux (GDT) ---
gdt_start:
    dq 0x0
gdt_code:
    dw 0xffff, 0x0, 0x9a00, 0x00cf
gdt_data:
    dw 0xffff, 0x0, 0x9200, 0x00cf
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start