CC=gcc
CFLAGS=-g -pedantic-errors -Wall

default: all

all: cserver cclient step1-server step2-server step1-client step2-client

cserver: cserver.o
	$(CC) -o cserver cserver.o

cserver.o: cserver.c 
	$(CC) -c cserver.c
	
cclient: cclient.o
	$(CC) -o cclient cclient.o

cclient.o: cclient.c 
	$(CC) -c cclient.c
	
step1-server: step1-server.o
	$(CC) -o step1-server step1-server.o

step1-server.o: step1-server.c 
	$(CC) -c step1-server.c
	
step2-server: step2-server.o
	$(CC) -o step2-server step2-server.o

step2-server.o: step2-server.c 
	$(CC) -c step2-server.c
	
step1-client: step1-client.o
	$(CC) -o step1-client step1-client.o

step1-client.o: step1-client.c 
	$(CC) -c step1-client.c
	
step2-client: step2-client.o
	$(CC) -o step2-client step2-client.o

step2-client.o: step2-client.c 
	$(CC) -c step2-client.c

.PHONY: clean

clean:
	rm -rf cserver cclient step1-server step2-server step1-client step2-client cserver.o cclient.o step1-server.o step2-server.o step1-client.o step2-client.o
