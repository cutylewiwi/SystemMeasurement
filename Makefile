CC=gcc
INCLUDE=./include
LIB=./lib

all: cpu

cpu: cycles time_ovh loop_ovh procedure syscall thread process

%.o : %.c $(DEPS)
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

thread.o: thread.c
	$(CC) -O0 -c -I$(INCLUDE) thread.c

process: process.o
	$(CC) -o process process.o

process.o: process.c
	$(CC) -O0 -c -I$(INCLUDE) process.c

lib: statistics.c
	$(CC) -c statistics.c

clean:
	rm *.o cycles time_ovh loop_ovh procedure syscall
