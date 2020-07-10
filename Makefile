all:
	gcc -o main.o main.c graph.c -I.
go:
	gcc -o main.o main.c graph.c -I. && ./main.o