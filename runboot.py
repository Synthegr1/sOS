import subprocess
import os

base = os.path.dirname(os.path.abspath(__file__))

os.chdir(os.path.join(base, "rust"))
subprocess.run(["rustc", "--emit=obj", "-C", "panic=abort", "-C", "opt-level=3", "-C", "overflow-checks=off", "--target", "i686-unknown-linux-gnu", "maths.rs", "-o", "../os/maths.o"])

os.chdir(os.path.join(base, "os"))
subprocess.run(["nasm", "-f", "elf32", "boot.asm", "-o", "boot.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "kernel.c", "-o", "kernel.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "shell.c", "-o", "shell.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "util.c", "-o", "util.o"])
subprocess.run(["gcc", "-m32", "-ffreestanding", "-fno-pie", "-nostdlib", "-c", "math.c", "-o", "math.o"])
subprocess.run(["ld", "-m", "elf_i386", "-T", "linker.ld", "boot.o", "kernel.o", "shell.o", "util.o", "math.o", "maths.o", "-o", "boot.elf"])
subprocess.run(["objcopy", "-O", "binary", "boot.elf", "boot.bin"])
subprocess.run(["qemu-system-i386", "-drive", "format=raw,file=boot.bin", "-d", "cpu_reset", "-D", "qemu.log"])
print("Successfull")