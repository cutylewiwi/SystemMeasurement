CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: access access_ptr bandwidth

access: access.o
	$(CC) -o access access.o

access.o: access.c
	$(CC) -I$(INCLUDE) -c access.c -O1

access_ptr: access_ptr.o
	$(CC) -o access_ptr access_ptr.o

access_ptr.o: access_ptr.c
	$(CC) -I$(INCLUDE) -c access_ptr.c -O1

bandwidth: bandwidth.o
	$(CC) -o bandwidth bandwidth.o

bandwidth.o: bandwidth.c
	$(CC) -I$(INCLUDE) -c bandwidth.c -O0

pagefault: pagefault.o
	$(CC) -o pagefault pagefault.o

pagefault.o: pagefault.c
	$(CC) -I$(INCLUDE) -c pagefault.c -O0

clean:
	rm *.o access access_ptr bandwidth pagefault
