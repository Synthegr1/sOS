import subprocess
import os


os.chdir("os")
subprocess.run(["nasm", "-f", "elf32", "boot.asm", "-o", "boot.o"])

subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "kernel.c", "-o", "kernel.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "shell.c", "-o", "shell.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "util.c", "-o", "util.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "math.c", "-o", "math.o"])

subprocess.run(["ld", "-m", "elf_i386", "-T", "linker.ld", "boot.o", "kernel.o", "shell.o", "util.o", "math.o", "-o", "boot.elf"])
subprocess.run(["objcopy", "-O", "binary", "boot.elf", "boot.bin"])
subprocess.run(["qemu-system-i386", "-drive", "format=raw,file=boot.bin", "-d", "cpu_reset", "-D", "qemu.log"])
print("Successfull")