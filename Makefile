all:
	gcc -o main.o main.c -I.
go:
	gcc -o main.o main.c -I. && ./main.o
test:
	gcc -o main.o test.c -I. && ./main.o