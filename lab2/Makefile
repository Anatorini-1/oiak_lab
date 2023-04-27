all: zad2 zad1

zad1: zad1.o
	ld zad1.o -o zad1 -m elf_i386
	

zad1.o: zad1.s
	as  --gstabs zad1.s -o zad1.o --32


zad2: zad2.o
	ld zad2.o -o zad2 -m elf_i386
	

zad2.o: zad2.s
	as  --gstabs zad2.s -o zad2.o --32

clean:
	rm zad2.o
	rm zad2
	rm zad1.o
	rm zad1