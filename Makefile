

CC=gcc
INCLUDE=./include

all: cpu

cpu: overhead

overhead: overhead.o
	$(CC) -o overhead overhead.o

overhead.o: overhead.c
	$(CC) -O0 -c -I$(INCLUDE) overhead.c



clean:
	rm *.o overhead
