TARGET = bin/kernel
CC = g++
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
              -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c \
              -Iinclude -O2

OBJECTS = obj/kasm.o obj/kc.o obj/framebuffer.o

DIRS = bin obj
$(shell mkdir -p $(DIRS))

all: $(TARGET)

$(TARGET): obj/kasm.o obj/kc.o obj/framebuffer.o
	ld -m elf_i386 -T src/link.ld -o $(TARGET) $(OBJECTS)

obj/kasm.o: src/kernel.s
	nasm -f elf32 src/kernel.s -o obj/kasm.o

obj/kc.o: src/main.c
	gcc $(CFLAGS) src/main.c -o obj/kc.o

obj/framebuffer.o: src/framebuffer.c
	gcc $(CFLAGS) src/framebuffer.c -o obj/framebuffer.o

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -rf $(DIRS)
