all: tak

tak: 
	as -o addInts.o addInts.s --32
	ld -shared -fPIC -o libAddInts.so addInts.o -m elf_i386
	g++ -o main main.cpp -L. -lAddInts -m32 -Wl,-rpath=. -m32