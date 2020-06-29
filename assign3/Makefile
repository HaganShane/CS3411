CC=gcc
CFLAGS=-g -pedantic-errors -Wall

default: dealer

all: step1 step2 step3 step4 step5 step6 step7 dealer

dealer: dealer.o
	$(CC) -o dealer dealer.o

dealer.o: dealer.c 
	$(CC) $(CFLAGS) -c dealer.c
	
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
	
step5: step5.o
	$(CC) -o step5 step5.o

step5.o: step5.c 
	$(CC) $(CFLAGS) -c step5.c

step6: step6.o
	$(CC) -o step6 step6.o

step6.o: step6.c 
	$(CC) $(CFLAGS) -c step6.c
	
step7: step7.o
	$(CC) -o step7 step7.o

step7.o: step7.c 
	$(CC) $(CFLAGS) -c step7.c
	

.PHONY: clean

clean:
	rm -rf step1 step1.o step2 step2.o step3 step3.o step4 step4.o step5 step5.o step6 step6.o step7 step7.o dealer dealer.o
