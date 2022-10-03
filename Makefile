CMD = gcc
BIN = bin
CFLAGS = -Wextra -Wall -march=native -O2
INC = ./common

all: tcpc tcps

tcps: tcpserver.o common.o
	$(CC) -o $(BIN)/tcps tcpserver.o common.o

tcpc: tcpclient.o common.o
	$(CC) -o $(BIN)/tcpc tcpclient.o common.o

tcpserver.o: tcpserver.c $(INC)/common.c
	$(CC) -c tcpserver.c $(INC)/common.c

tcpclient.o: tcpclient.c $(INC)/common.c
	$(CC) -c tcpclient.c $(INC)/common.c

.PHONY: clean

clean:
	rm ./*.o
