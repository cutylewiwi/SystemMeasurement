CC=gcc
INCLUDE=./include
LIB=./lib

all: cpu

cpu: cycles time_ovh loop_ovh procedure syscall

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

clean:
	rm *.o cycles time_ovh loop_ovh procedure syscall
