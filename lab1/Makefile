all: add


add: add.o
	ld add.o -o add -g -m elf_i386
	rm add.o
	clear
	./add

add.o: add.s
	as add.s -o add.o -g -32

clear:
	rm add
	rm add.o