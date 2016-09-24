#lib math.h
lib = -lm
src = main

all: cleanBefore functions.o main.o main clean

main: functions.o main.o
	gcc -o cgSolver functions.o $(src).o $(lib)

main.o: main.c
	gcc -o $(src).o -c $(src).c

functions.o: functions.c
	gcc -o functions.o -c functions.c

cleanBefore:
	rm -rf cgSolver

clean:
	rm -rf *.o *~