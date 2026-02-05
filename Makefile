ARCH := x86_64
CC   := x86_64-elf-gcc
LD   := x86_64-elf-ld
AS   := nasm

BUILD := build

CFLAGS := -g -O2 -ffreestanding -Wall -Wextra \
          -fno-pie -mno-red-zone -mcmodel=kernel \
          -I include

ASFLAGS := -f elf64
LDFLAGS := -T arch/x86/boot/linker.ld -nostdlib

# ===============================
# Object files
# ===============================

OBJS := \
$(BUILD)/start.o \
$(BUILD)/kmain.o \
$(BUILD)/idt.o \
$(BUILD)/irq.o \
$(BUILD)/lapic.o \
$(BUILD)/serial.o \
$(BUILD)/vga.o \
$(BUILD)/keyboard_c.o \
$(BUILD)/keyboard_s.o \
$(BUILD)/idt0_c.o \
$(BUILD)/idt0_s.o \
$(BUILD)/idt8_c.o \
$(BUILD)/idt8_s.o \
$(BUILD)/idt13_c.o \
$(BUILD)/idt13_s.o \
$(BUILD)/idt14_c.o \
$(BUILD)/idt14_s.o \
$(BUILD)/idt32_c.o \
$(BUILD)/idt32_s.o \
$(BUILD)/idt67_c.o \
$(BUILD)/idt67_s.o \
$(BUILD)/panic.o \
$(BUILD)/log.o

# ===============================
# Targets
# ===============================

all: dootix.iso

$(BUILD):
	mkdir -p $(BUILD)

# ===============================
# Boot
# ===============================

$(BUILD)/start.o: arch/x86/boot/start.S | $(BUILD)
	$(AS) $(ASFLAGS) $< -o $@

# ===============================
# Kernel core
# ===============================

$(BUILD)/kmain.o: kernel/kmain.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/panic.o: kernel/panic/panic.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/log.o: kernel/log/log.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# CPU / Interrupts
# ===============================

$(BUILD)/idt.o: arch/x86/cpu/idt/idt.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/irq.o: arch/x86/cpu/irq/irq.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/lapic.o: arch/x86/cpu/apic/lapic/lapic.c
	$(CC) $(CFLAGS) -c $< -o $@


# ===============================
# ISR vectors
# ===============================

$(BUILD)/idt0_c.o: arch/x86/cpu/isr/idt_0/idt_0.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/idt0_s.o: arch/x86/cpu/isr/idt_0/idt_0.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/idt8_c.o: arch/x86/cpu/isr/idt_8/idt_8.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/idt8_s.o: arch/x86/cpu/isr/idt_8/idt_8.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/idt13_c.o: arch/x86/cpu/isr/idt_13/idt_13.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/idt13_s.o: arch/x86/cpu/isr/idt_13/idt_13.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/idt14_c.o: arch/x86/cpu/isr/idt_14/idt_14.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/idt14_s.o: arch/x86/cpu/isr/idt_14/idt_14.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/idt32_c.o: arch/x86/cpu/isr/idt_32/idt_32.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/idt32_s.o: arch/x86/cpu/isr/idt_32/idt_32.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/idt67_c.o: arch/x86/cpu/isr/idt_67/idt_67.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/idt67_s.o: arch/x86/cpu/isr/idt_67/idt_67.s
	$(AS) $(ASFLAGS) $< -o $@

# ===============================
# Platform drivers
# ===============================

$(BUILD)/serial.o: arch/x86/platform/serial/serial.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/vga.o: arch/x86/platform/vga/vga.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/keyboard_c.o: arch/x86/platform/keyboard/keyboard.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/keyboard_s.o: arch/x86/platform/keyboard/keyboard.s
	$(AS) $(ASFLAGS) $< -o $@

# ===============================
# Linking
# ===============================

$(BUILD)/kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

dootix.iso: $(BUILD)/kernel.elf
	cp $< isodir/boot/kernel.elf
	grub-mkrescue -o dootix.iso isodir

run: dootix.iso
	qemu-system-x86_64 -cdrom dootix.iso -serial stdio

test: dootix.iso
	qemu-system-x86_64 -cdrom dootix.iso -serial stdio -s -S

clean:
	rm -rf build dootix.iso
