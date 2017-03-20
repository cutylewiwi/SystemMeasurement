CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: access_ptr bandwidth_reading pagefault largefile bandwidth_writing

access_ptr: access_ptr.o
	$(CC) -o access_ptr access_ptr.o

access_ptr.o: access_ptr.c
	$(CC) -I$(INCLUDE) -c access_ptr.c -O1

bandwidth_reading: bandwidth_reading.o
	$(CC) -o bandwidth_reading bandwidth_reading.o

bandwidth_reading.o: bandwidth_reading.c
	$(CC) -I$(INCLUDE) -c bandwidth_reading.c -O1

bandwidth_writing: bandwidth_writing.o
	$(CC) -o bandwidth_writing bandwidth_writing.o

bandwidth_writing.o: bandwidth_writing.c
	$(CC) -I$(INCLUDE) -c bandwidth_writing.c -O1

pagefault: pagefault.o
	$(CC) -o pagefault pagefault.o

pagefault.o: pagefault.c
	$(CC) -I$(INCLUDE) -c pagefault.c -O0

largefile: largefile.c
	$(CC) -o largefile largefile.c -O1

clean:
	rm *.o access_ptr bandwidth_reading pagefault largefile bandwidth_writing
