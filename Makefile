

CC=gcc
INCLUDE=./include
LIB=./lib

all: cpu

cpu: cycles time_ovh loop_ovh procedure syscall thread process

time_ovh: time_ovh.o
	$(CC) -o time_ovh time_ovh.o

time_ovh.o: time_ovh.c
	$(CC) -O0 -c -I$(INCLUDE) time_ovh.c

loop_ovh: loop_ovh.o
	$(CC) -o loop_ovh loop_ovh.o
	
loop_ovh.o: loop_ovh.c
	$(CC) -O0 -c -I$(INCLUDE) loop_ovh.c

cycles: cycles.o
	$(CC) -o cycles cycles.o

cycles.o: cycles.c
	$(CC) -O0 -c -I$(INCLUDE) cycles.c

loop: loop.o
	$(CC) -o loop loop.o

loop.o: loop.c
	$(CC) -O0 -c -I$(INCLUDE) loop.c

procedure: procedure.o
	$(CC) -o procedure procedure.o

procedure.o: procedure.c
	$(CC) -O0 -c -I$(INCLUDE) procedure.c

syscall: syscall.o
	$(CC) -o syscall syscall.o

syscall.o: syscall.c
	$(CC) -O0 -c -I$(INCLUDE) syscall.c

thread: thread.o
	$(CC) -pthread -o thread thread.o

thread.o: thread.c
	$(CC) -O0 -c -I$(INCLUDE) thread.c

process: process.o
	$(CC) -o process process.o

process.o: process.c
	$(CC) -O0 -c -I$(INCLUDE) process.c

lib: statistics.c
	$(CC) -c statistics.c

clean:
	rm *.o cycles overhead loop procedure
