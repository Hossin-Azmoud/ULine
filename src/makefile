CC=gcc
CFLAGS=-Wall -std=c11 -Wextra

all: main

# Compiling the ULine lib.
ULine.o: ULine.c ULine.h
	$(CC) $(CFLAGS) -c ULine.c

# Compiling the chunk lib.
chunk.o: chunk.c chunk.h
	$(CC) $(CFLAGS) -c chunk.c

# Linking all.
main: main.c ULine.o chunk.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	del *.o
