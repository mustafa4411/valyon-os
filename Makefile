CC = gcc
CFLAGS = -m32 -ffreestanding -fno-stack-protector -nostdlib -nodefaultlibs

all: iso

kernel:
	$(CC) $(CFLAGS) -T kernel/linker.ld -o iso/boot/kernel.bin kernel/kernel.c -lgcc

iso: kernel
	grub-mkrescue -o valyonos.iso iso

clean:
	rm -f iso/boot/kernel.bin valyonos.iso
