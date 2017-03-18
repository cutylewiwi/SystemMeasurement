CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib
TARGET=rtt peak setup teardown close server
SERVER_IP=172.19.222.54
SERVER_PORT=9011

all: network

network: $(TARGET)

%.o : %.c
	$(CC) -O0 -c $(CFLAGS) -I$(INCLUDE) $<

% : %.o
	$(CC) -o $< $<.o

local_server: server
	./server $(SERVER_PORT) &
	sleep 1

remote_server: server	
	ssh heyihong@$(SERVER_IP) ~/server $(SERVER_PORT) &
	sleep 1

benchmark: network local_server remote_server
	./rtt 127.0.0.1 $(SERVER_PORT) 10000 > local_rtt.result
	./setup 127.0.0.1 $(SERVER_PORT) 10000 > local_setup.result
	./teardown 127.0.0.1 $(SERVER_PORT) 10000 > local_teardown.result
	./close 127.0.0.1 $(SERVER_PORT)
	./rtt $(SERVER_IP) $(SERVER_PORT) 10000 > remote_rtt.result
	./setup $(SERVER_IP) $(SERVER_PORT) 10000 > remote_setup.result
	./teardown $(SERVER_IP) $(SERVER_PORT) 10000 > remote_teardown.result
	./close $(SERVER_IP) $(SERVER_PORT)

clean:
	rm -f *.o $(TARGET)
