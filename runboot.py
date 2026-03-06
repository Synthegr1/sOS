import subprocess
import os


os.chdir("os")
subprocess.run(["nasm", "-f", "elf32", "boot.asm", "-o", "boot.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "kernel.c", "-o", "kernel.o"])
subprocess.run(["ld", "-m", "elf_i386", "-T", "linker.ld", "boot.o", "kernel.o", "-o", "boot.elf"])
subprocess.run(["objcopy", "-O", "binary", "boot.elf", "boot.bin"])
subprocess.run(["qemu-system-i386", "-drive", "format=raw,file=boot.bin", "-d", "cpu_reset", "-D", "qemu.log"])
print("Successfull")