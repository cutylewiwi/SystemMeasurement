CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib
TARGET=rtt peak setup teardown close server
SERVER_IP=172.19.222.54
SERVER_PORT=9000

all: network

network: $(TARGET)

%.o : %.c
		$(CC) -O0 -c $(CFLAGS) -I$(INCLUDE) $<

% : %.o
		$(CC) -o $< $<.o

local_server: server
		./server $(SERVER_PORT) &

remote_server: server
        scp ./server heyihong@$(SERVER_IP):~
		ssh heyihong@$(SERVER_IP) ~/server $(SERVER_PORT) &

benchmark: network local_server remote_server
		./rtt 127.0.0.1 $(SERVER_PORT) 10000 > rtt.result
		./setup 127.0.0.1 $(SERVER_PORT) 10000 > setup.result
		./teardown 127.0.0.1 $(SERVER_PORT) 10000 > teardown.result
		./close 127.0.0.1 $(SERVER_PORT)
		./rtt $(SERVER_IP) $(SERVER_PORT) 10000 > rtt.result
		./setup $(SERVER_IP) $(SERVER_PORT) 10000 > setup.result
		./teardown $(SERVER_IP) $(SERVER_PORT) 10000 > teardown.result
		./close $(SERVER_IP) $(SERVER_PORT)

clean:
		rm -f *.o $(TARGET)