CC=gcc
CFLAGS=-g -pedantic-errors -Wall

default: all

all: arraysum

arraysum: arraysum.o
	$(CC) -o arraysum arraysum.o

arraysum.o: arraysum.c arraysum.h
	$(CC) $(CFLAGS) -c arraysum.c

.PHONY: clean

clean:
	rm -rf arraysum arraysum.o
