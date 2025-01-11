all: build/init


build/init:
	gcc -g -ffreestanding -m32 -fno-pie -nostdlib \
		-Wl,-T,link.ld \
		-Wl,--oformat=binary \
		-o build/init \
		-Iinclude \
		src/init.c src/usyscall.c

	