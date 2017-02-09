CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib

all: cpu

cpu: cycles time_ovh loop_ovh procedure syscall thread process proc_switch thread_switch

%.o : %.c
	$(CC) -O0 -c $(CFLAGS) -I$(INCLUDE) $<

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

thread: thread.o
	$(CC) -pthread -o thread thread.o

process: process.o
	$(CC) -o process process.o

proc_switch: proc_switch.o
	$(CC) -o proc_switch proc_switch.o

thread_switch: thread_switch.o
	$(CC) -pthread -o thread_switch thread_switch.o

clean:
	rm -f *.o cycles time_ovh loop_ovh procedure syscall thread process proc_switch thread_switch
