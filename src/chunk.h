#ifndef CHUNK_H

#define CHUNK_H
#define CHUNK_SIZE 1024
#define READ_ALL   0

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
typedef struct Chunk {
    void   *bytes; 
    size_t size;
    size_t cap;
} Chunk;

typedef struct Chunks {
    Chunk  *items;
    size_t size;
    size_t cap;
} Chunks;

// Loader.
int    load(FILE *Stream, Chunk *chunk);
Chunks *load_all(FILE *Stream);

// dumpers.
int    chunk_dump(FILE *Stream, Chunk *chunk);
int    chunks_dump(FILE *Stream, Chunks *chunks);

// Allocators. 
Chunk  *AllocChunk(size_t cap);
Chunks *AllocChunks(size_t cap, size_t amount);

// Util
long get_file_size(FILE *Stream);
void report_usage(Chunk *chunk);
void  chunk_memcheck(Chunk *chunk, size_t offset, bool movebuff); // check if the allocated mem in Line->content

void  MemGrow(Chunk *chunk, size_t amount);

#endif // CHUNK_H
