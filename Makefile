all:
	gcc -o main.o main.c -I.
go:
	gcc -o main.o main.c -I. && ./main.o