CC=gcc
CFLAGS=-pipe
INC=

all: Simulator
	$(CC) $(CFLAGS) Simulator.o -o Simulator

Simulator: Simulator.c
	$(CC) $(CFLAGS) -c Simulator.c

dist:
	tar -cvjf dist.tbz2 Simulator.c Makefile

clean:
	rm  Simulator.o Simulator
