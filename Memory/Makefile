CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: access access_ptr

access: access.o
	$(CC) -o access access.o

access.o: access.c
	$(CC) -I$(INCLUDE) -c access.c -O1

access_ptr: access_ptr.o
	$(CC) -o access_ptr access_ptr.o

access_ptr.o: access_ptr.c
	$(CC) -I$(INCLUDE) -c access_ptr.c -O1

clean:
	rm *.o access
