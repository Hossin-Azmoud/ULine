#ifndef CHUNK_H

#define CHUNK_H
#define CHUNK_SIZE 1024
#define READ_ALL   0

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

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
Chunk *allocChunk(size_t cap);
Chunks *allocChunks(size_t cap, size_t amount);

// Util
long get_file_size(FILE *Stream);
void report_usage(Chunk *chunk);

#endif // CHUNK_H
