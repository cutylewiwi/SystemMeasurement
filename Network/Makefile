CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib
TARGET=rtt peak setup teardown server

all: network

network: $(TARGET)

%.o : %.c
	$(CC) -O0 -c $(CFLAGS) -I$(INCLUDE) $<

% : %.o
	$(CC) -o $< $<.o

clean:
	rm -f *.o $(TARGET)
