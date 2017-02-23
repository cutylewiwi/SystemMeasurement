CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: access

access: access.o
	$(CC) -o access access.o

access.o: access.c
	$(CC) -I$(INCLUDE) -c access.c

clean:
	rm *.o access
