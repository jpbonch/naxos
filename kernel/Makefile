all: ../build/main.o ../build/puts.o

../build/main.o: src/main.c
	gcc -g -ffreestanding -m32 -c src/main.c -o ../build/main.o -fno-pie -Iinclude

../build/puts.o: src/puts.c
	gcc -g -ffreestanding -m32 -c src/puts.c -o ../build/puts.o -fno-pie -Iinclude