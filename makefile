SRC=$(shell find . -name '*.[c,h]')
CC=gcc
CFLAGS=-Werror -Wall -g
LDFLAGS=-lpthread 

all : clean main

main : $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean :
	@rm -f main
