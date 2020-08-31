CFLAGS=-Wall -fpic -ffreestanding -fno-stack-protector -nostdinc -nostdlib -mno-red-zone -Iextern
LDFLAGS=-nostdlib -nostartfiles
CC=clang
LD=ld

all: uan.iso

uan.iso: kernel.elf
	mkdir -p build/release
	mkdir -p build/iso/UEFI/EFI/BOOT
	mkdir -p build/iso/boot
	cp config/boot.config build/iso/boot
	cp build/bin/kernel.elf build/iso/boot
	../bootboot/mkbootimg/mkbootimg config/image.json build/release/uan.iso

kernel.elf:
	mkdir -p build/obj
	mkdir -p build/bin
	$(CC) $(CFLAGS) -c src/kernel.c -o build/obj/kernel.o
	$(LD) -r -b binary -o build/obj/font.o font.psf
	$(LD) $(LDFLAGS) -T src/link.ld build/obj/kernel.o build/obj/font.o -o build/bin/kernel.elf

clean:
	rm -f build/obj/*
	rm -f build/bin/*
	rm -f -r build/iso/*

clean-full:
	rm -f -r build/*
