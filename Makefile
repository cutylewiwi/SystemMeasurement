

CC=gcc
INCLUDE=./include
LIB=./lib

all: cpu

cpu: cycles overhead loop

overhead: overhead.o
	$(CC) -o overhead overhead.o

overhead.o: overhead.c
	$(CC) -O0 -c -I$(INCLUDE) overhead.c

cycles: cycles.o
	$(CC) -o cycles cycles.o

cycles.o: cycles.c
	$(CC) -O0 -c -I$(INCLUDE) cycles.c

loop: loop.o
	$(CC) -o loop loop.o

loop.o: loop.c
	$(CC) -O0 -c -I$(INCLUDE) loop.c

lib: statistics.c
	$(CC) -c statistics.c

clean:
	rm *.o cycles overhead loop
