

CC=gcc
INCLUDE=./include
LIB=./lib

all: cpu

cpu: cycles overhead

overhead: overhead.o
	$(CC) -o overhead overhead.o

overhead.o: overhead.c
	$(CC) -O0 -c -I$(INCLUDE) overhead.c

cycles: cycles.o
	$(CC) -o cycles cycles.o

cycles.o: cycles.c
	$(CC) -O0 -c -I$(INCLUDE) cycles.c

lib: statistics.c
	$(CC) -c statistics.c

clean:
	rm *.o cycles overhead
