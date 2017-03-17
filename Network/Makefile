CC=gcc
INCLUDE=../include
CFLAGS = -Wall
LIB=../lib
TARGET=rtt peak setup teardown close server
SERVER_IP=172.19.222.54
SERVER_PORT=9003

all: network

network: $(TARGET)

%.o : %.c
	$(CC) -O0 -c $(CFLAGS) -I$(INCLUDE) $<

% : %.o
	$(CC) -o $< $<.o

remote_server: server	
	ssh heyihong@$(SERVER_IP) rm ~/server &
	scp ./server heyihong@$(SERVER_IP):~
	ssh heyihong@$(SERVER_IP) ~/server $(SERVER_PORT) &
	sleep 1

benchmark: network remote_server
	./rtt $(SERVER_IP) $(SERVER_PORT) 10000 > rtt.result
	./setup $(SERVER_IP) $(SERVER_PORT) 10000 > setup.result
	./teardown $(SERVER_IP) $(SERVER_PORT) 10000 > teardown.result
	./close $(SERVER_IP) $(SERVER_PORT)

clean:
	rm -f *.o $(TARGET)
