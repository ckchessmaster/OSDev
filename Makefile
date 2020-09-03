CC++	:= clang++
CC		:= clang
LD		:= ld

CFLAGS	=-Wall -fpic -ffreestanding -fno-stack-protector -mno-red-zone -fno-rtti -fno-exceptions -Iextern
LDFLAGS	=-nostdlib -nostartfiles

SRC     := src
BUILD	:= build
OBJ     := $(BUILD)/obj
BIN     := $(BUILD)/bin
RELEASE := $(BUILD)/release/uan.iso

SRCS    := $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/**/*.cpp)
OBJS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
KERNEL  := $(BIN)/kernel.elf

.PHONY: all setup clean clean-full

all: setup $(RELEASE)

$(RELEASE): $(KERNEL)
	cp config/boot.config build/iso/boot
	cp build/bin/kernel.elf build/iso/boot
	../bootboot/mkbootimg/mkbootimg config/image.json build/release/uan.iso

$(KERNEL): $(OBJS) | $(BIN)
	$(LD) -r -b binary -o build/obj/font.o font.psf
	$(LD) $(LDFLAGS) -T src/link.ld build/obj/font.o $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC++) $(CFLAGS) -c $< -o $@

setup:
	mkdir -p build/obj/libc
	mkdir -p build/bin
	mkdir -p build/release
	mkdir -p build/iso/UEFI/EFI/BOOT
	mkdir -p build/iso/boot

clean:
	rm -f -r build/obj/*
	rm -f build/bin/*
	rm -f -r build/iso/*

clean-full:
	rm -f -r build/*
