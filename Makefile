#lib math.h
lib = -lm
src = main

all: cleanBefore functions.o main.o main cleanMake

main: functions.o main.o
	gcc -o cgSolver functions.o $(src).o $(lib)

main.o: main.c
	gcc -std=c99 -o $(src).o -c $(src).c

functions.o: functions.c
	gcc -std=c99 -o functions.o -c functions.c

cleanBefore:
	rm -rf cgSolver

clean:
	rm -rf *.o *~ cgSolver
	
cleanMake:
	rm -rf *.o *~