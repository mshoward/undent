CC=g++
CFLAGS=-std=c++11 -c -Wall -g
LFLAGS=

all: undent

undent: undent.o
	$(CC) $(LFLAGS) -o undent undent.o

undent.o: undent.cpp
	$(CC) $(CFLAGS) undent.cpp

clean:
	rm -rf *o undent
