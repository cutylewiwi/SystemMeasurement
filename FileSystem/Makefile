CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: genfile filecache seqread randread contention

filecache: filecache.o
	$(CC) -o filecache filecache.o

filecache.o: filecache.c
	$(CC) -I$(INCLUDE) -c filecache.c -O0

seqread: seqread.o
	$(CC) -o seqread seqread.o

seqread.o: seqread.c
	$(CC) -I$(INCLUDE) -c seqread.c -O0

randread: randread.o
	$(CC) -o randread randread.o

randread.o: randread.c
	$(CC) -I$(INCLUDE) -c randread.c -O0 

genfile: genfile.o
	$(CC) -o genfile genfile.o

genfile.o: genfile.c
	$(CC) -I$(INCLUDE) -c genfile.c -O0

contention: contention.o
	$(CC) -o contention contention.o

contention.o: contention.c
	$(CC) -I$(INCLUDE) -c contention.c -O0
