# Make sure to use tabs (NOT spaces)
CFLAGS=-Wall -g

all: main

## linker will barf, as multiple definitions of same function fib()
#main: fib1.o fib2.o

## This is ok
main: fib1.o

## This is ok too
#main: fib2.o

clean:
	rm -rf main; \
	rm -rf *.o;
