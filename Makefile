CC=gcc
INCLUDE=./include
LIB=./lib

all: cpu

cpu: cycles time_ovh loop_ovh procedure syscall thread process

%.o : %.c
	$(CC) -O0 -c -I$(INCLUDE) $< 

time_ovh: time_ovh.o
	$(CC) -o time_ovh time_ovh.o

loop_ovh: loop_ovh.o
	$(CC) -o loop_ovh loop_ovh.o
	
cycles: cycles.o
	$(CC) -o cycles cycles.o

loop: loop.o
	$(CC) -o loop loop.o

procedure: procedure.o
	$(CC) -o procedure procedure.o

syscall: syscall.o
	$(CC) -o syscall syscall.o

syscall.o: syscall.c
	$(CC) -O0 -c -I$(INCLUDE) syscall.c

thread: thread.o
	$(CC) -pthread -o thread thread.o

process: process.o
	$(CC) -o process process.o

clean:
	rm *.o cycles time_ovh loop_ovh procedure syscall thread process
