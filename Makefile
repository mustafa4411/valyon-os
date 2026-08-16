CC = gcc
CFLAGS = -m32 -ffreestanding -fno-stack-protector -nostdlib -nodefaultlibs

all: iso

kernel:
	$(CC) $(CFLAGS) -T kernel/linker.ld -o iso/boot/kernel.bin kernel/kernel.c -lgcc

iso: kernel
	xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso -o valyonos.iso
	~/limine/limine bios-install valyonos.iso

clean:
	rm -f iso/boot/kernel.bin valyonos.iso
