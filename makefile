# Définition des compilateurs et outils
RUSTC = rustc
NASM = nasm
CC = gcc
LD = ld
OBJCOPY = objcopy
QEMU = qemu-system-i386

# Drapeaux de compilation (Flags)
RUSTCFLAGS = --emit=obj -C panic=abort -C opt-level=3 -C overflow-checks=off --target i686-unknown-linux-gnu
NASMFLAGS = -f elf32
CFLAGS = -m32 -ffreestanding -fno-pie -nostdlib
LDFLAGS = -m elf_i386 -T $(OS_DIR)/linker.ld

# Définition des répertoires
RUST_DIR = rust
OS_DIR = os

# Liste des objets nécessaires dans le dossier os/
OBJS = $(OS_DIR)/boot.o \
       $(OS_DIR)/kernel.o \
       $(OS_DIR)/shell.o \
       $(OS_DIR)/util.o \
       $(OS_DIR)/math.o \
       $(OS_DIR)/maths.o

# Règle par défaut : lance QEMU
all: run

# Lancement de QEMU
run: $(OS_DIR)/boot.bin
	@echo "QEMU is starting..."
	$(QEMU) -drive format=raw,file=$(OS_DIR)/boot.bin -d cpu_reset -D qemu.log
	@echo "Successful"

    
# Création du binaire final
$(OS_DIR)/boot.bin: $(OS_DIR)/boot.elf
	$(OBJCOPY) -O binary $< $@
	@echo "Binary created"

# Édition de liens (Linking)
$(OS_DIR)/boot.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@
	@echo "Linking done"

# Compilation du fichier Rust
$(OS_DIR)/maths.o: $(RUST_DIR)/maths.rs
	$(RUSTC) $(RUSTCFLAGS) $< -o $@

# Compilation de l'assembleur NASM
$(OS_DIR)/%.o: $(OS_DIR)/%.asm
	$(NASM) $(NASMFLAGS) $< -o $@

# Compilation des fichiers C
$(OS_DIR)/%.o: $(OS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OS_DIR)/*.o $(OS_DIR)/*.elf $(OS_DIR)/*.bin qemu.log