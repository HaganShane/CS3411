CC=gcc
CFLAGS=-g -pedantic-errors -Wall

default: all

all: filestats

filestats: filestats.o
	$(CC) -o filestats filestats.o

arraysum.o: filestats.c
	$(CC) $(CFLAGS) -c filestats.c

.PHONY: clean

clean:
	rm -rf filestats filestats.o
