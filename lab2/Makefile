all: float

float: float.o
	ld float.o -o float -m elf_i386
	gdb float

float.o: float.s
	as  --gstabs float.s -o float.o --32

clean:
	rm float.o
	rm float