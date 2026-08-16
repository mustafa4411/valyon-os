```markdown
# ValyonOS

A lightweight 32-bit x86 operating system featuring direct VGA text-mode rendering, a basic PS/2 keyboard driver, and built-in runtime keyboard layout switching (English US / Turkish Q).

## Features

- **32-Bit Bare-Metal Kernel:** Compiled with GCC in 32-bit freestanding mode (`-m32 -ffreestanding`).
- **Multiboot Compliant:** Uses a standard Multiboot header loaded at `0x100000`.
- **Direct VGA Text Rendering:** Custom screen driver utilizing color video memory (`0xB8000`) for text output and cursor tracking.
- **PS/2 Keyboard Input:** Port I/O polling via standard PS/2 controller ports (`0x60`, `0x64`).
- **Dual Keyboard Layouts:** Dynamic layout switching via function keys:
  - **F1**: English US layout (`[EN]`)
  - **F2**: Turkish Q layout (`[TR]`)

```

## Prerequisites

Ensure you have the following tools installed on your build environment:

- **GCC / `libgcc`** (32-bit compilation target support)
- **`xorriso`** (ISO image creation)
- **Limine Bootloader** (installed at `~/limine/limine`)
- **QEMU** (for running the built OS)

## Building & Running

### 1. Build the ISO Image
Compile the kernel and assemble the bootable ISO file using `make`:

```bash
make

```

This compiles `kernel/kernel.c` using `kernel/linker.ld`, outputs `iso/boot/kernel.bin`, and creates a bootable hybrid ISO named `valyonos.iso` with Limine BIOS installation.

### 2. Run with QEMU

Launch the created ISO inside QEMU:

```bash
qemu-system-i386 -cdrom valyonos.iso

```

### 3. Cleaning Up

Remove built binaries and ISO files:

```bash
make clean

```

## Usage

When booted into ValyonOS:

* Type directly using your keyboard.
* Press **F1** to switch to the **English US** keyboard layout.
* Press **F2** to switch to the **Turkish Q** keyboard layout.

## License

This project is licensed under the **GNU General Public License v3.0** (GPL-3.0) - see the [LICENSE](https://github.com/mustafa4411/valyon-os/blob/main/LICENSE) file for details.
