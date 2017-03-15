CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: filecache

filecache: filecache.o
	$(CC) -o filecache filecache.o

filecache.o: filecache.c
	$(CC) -I$(INCLUDE) -c filecache.c -O0
