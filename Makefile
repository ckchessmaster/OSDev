CC=clang
CFLAGS=-target x86_64-elf -ffreestanding -mno-red-zone
LDFLAGS=-target x86_64-elf -nostdlib

uan.img: setup kernel.elf
	mkdir -p tmp/EFI/BOOT
	cp BOOTX64.EFI tmp/EFI/BOOT
	cp bin/kernel.elf tmp
	cp tomatboot.cfg tmp
	python3 ../image-builder/image-builder.py image-builder.yaml
	mv uan.img release
	cp release/uan.img release/uan.hdd
	rm -r tmp

kernel.elf: setup kernel.o
	$(CC) $(LDFLAGS) -o bin/kernel.elf obj/kernel.o -T src/linker.ld

kernel.o: setup
	$(CC) $(CFLAGS) -c -o obj/kernel.o src/kernel.c

setup:
	mkdir -p obj
	mkdir -p bin
	mkdir -p release

clean:
	rm -f obj/*
	rm -f bin/*