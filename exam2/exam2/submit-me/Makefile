CC=gcc
CFLAGS=-g
SUBMIT=pipes select
SUBMITC=$(SUBMIT:=.c) datafile Makefile

all: $(SUBMIT) 

%: %.c
	$(CC) $(CFLAGS) -o $@ $@.c

.PHONY: clean package

package: $(SUBMITC)
	tar -cvzf submit-me.tgz $(SUBMITC)

clean:
	rm -f $(SUBMIT) submit-me.tgz
