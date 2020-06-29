CC=gcc
CFLAGS=-g -pedantic-errors -Wall

default: all

all: ctar step1 step2 step3 step4

ctar: ctar.o
	$(CC) -o ctar ctar.o

ctar.o: ctar.c 
	$(CC) $(CFLAGS) -c ctar.c
	
step1: step1.o
	$(CC) -o step1 step1.o

step1.o: step1.c 
	$(CC) $(CFLAGS) -c step1.c
	
step2: step2.o
	$(CC) -o step2 step2.o

step2.o: step2.c 
	$(CC) $(CFLAGS) -c step2.c
	
step3: step3.o
	$(CC) -o step3 step3.o

step3.o: step3.c 
	$(CC) $(CFLAGS) -c step3.c
	
step4: step4.o
	$(CC) -o step4 step4.o

step4.o: step4.c 
	$(CC) $(CFLAGS) -c step4.c

.PHONY: clean

clean:
	rm -rf ctar ctar.o step1 step1.o step2 step2.o step3 step3.o step4 step4.o
