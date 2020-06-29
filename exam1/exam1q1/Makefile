CC=gcc
CFLAGS=-g
SUBMIT=fd-exec leak
SUBMITC=$(SUBMIT:=.c)

all: $(SUBMIT) 

%: %.c
	$(CC) $(CFLAGS) -o $@ $@.c

.PHONY: clean package

package: $(SUBMITC)
	tar -cvzf submit-me.tgz $(SUBMITC)

clean:
	rm -f $(SUBMIT) submit-me.tgz
