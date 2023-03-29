CC=gcc
CFLAGS=-Wall -std=c11 -Wextra

# LIBS Compile
all: read_and_write_chunks readfile read_lines_ use_util writefile

# Compiling the ULine lib.
ULine.o: ../ULine.c ../ULine.h
	$(CC) $(CFLAGS) -c ../ULine.c

# Compiling the chunk lib.
chunk.o: ../chunk.c ../chunk.h
	$(CC) $(CFLAGS) -c ../chunk.c

# read_write_chunks.
read_and_write_chunks: read_and_write_chunks.c ULine.o chunk.o
	$(CC) $(CFLAGS) -o $@ $^
	
readfile: readfile.c ULine.o
	$(CC) $(CFLAGS) -o $@ $^

read_lines_: read_lines_.c ULine.o
	$(CC) $(CFLAGS) -o $@ $^

use_util: use_util.c ULine.o
	$(CC) $(CFLAGS) -o $@ $^

writefile: writefile.c  ULine.o
	$(CC) $(CFLAGS) -o $@ $^
	move *.exe ./bin

clean:
	del *.o
	del .\bin\*.exe
