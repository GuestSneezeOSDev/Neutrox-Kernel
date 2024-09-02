############################
#	     MAKEFILE	       #
############################

TARGET = ../boot/kernel.bin

ASM_SOURCES = kernel_entry.asm
C_SOURCES = kernel.c

ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)

CC = gcc
LD = ld
ASM = nasm
CFLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -Wextra
LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary

all: $(TARGET)

$(TARGET): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(ASM_OBJECTS) $(C_OBJECTS)

%.o: %.asm
	$(ASM) -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean