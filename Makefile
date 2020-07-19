all:
	gcc -o main.o main.c -I. -lm

go:
	gcc -o main.o main.c -I. -lm && ./main.o

test:
	gcc -o main.o test.c -I. -lm && ./main.o

test2:
	gcc -o main.o test2.c -I. -lm && ./main.o
run:
	./main.o