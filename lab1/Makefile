all: add subb


add: add.o
	ld add.o -o add  -m elf_i386
	rm add.o

add.o: add.s
	as --gstabs add.s -o add.o  -32



subb: subb.o
	ld subb.o -o subb  -m elf_i386
	rm subb.o

subb.o: subb.s
	as --gstabs subb.s -o subb.o  -32
clear:
	rm add
	rm add.o
	rm subb
	rm subb.o