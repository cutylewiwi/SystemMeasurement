CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib
TARGET=rtt peak conn close server
SERVER=dyn54.sysnet.ucsd.edu
PORT=9014

all: network

network: $(TARGET)

%.o : %.c
	$(CC) -O0 -c $(CFLAGS) -I$(INCLUDE) $<

% : %.o
	$(CC) -o $< $<.o

local_server: server
	./server $(PORT) &
	sleep 0.5

remote_server: server	
	ssh heyihong@$(SERVER) ~/server $(PORT) &
	sleep 0.5

rtt-benchmark: rtt close local_server remote_server
	./rtt 127.0.0.1 $(PORT) 10000
	./rtt $(SERVER) $(PORT) 10000
	sleep 0.5
	./close 127.0.0.1 $(PORT)
	./close $(SERVER) $(PORT)

conn-benchmark: conn close local_server remote_server
	./conn 127.0.0.1 $(PORT) 1000
	./conn $(SERVER) $(PORT) 1000
	sleep 0.5
	./close 127.0.0.1 $(PORT)
	./close $(SERVER) $(PORT)

peak-benchmark: peak close local_server remote_server
	./peak 127.0.0.1 $(PORT) 1 5000000
	./peak $(SERVER) $(PORT) 1 5000000
	sleep 0.5
	./close 127.0.0.1 $(PORT)
	./close $(SERVER) $(PORT)


clean:
	rm -f *.o $(TARGET)
