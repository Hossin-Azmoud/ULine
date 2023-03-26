#ifndef CHUNK_H

#define CHUNK_H
#define CHUNK_SIZE 1024
#define READ_ALL   0

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Chunk {
    int    *bytes;
    size_t size;
    size_t cap;
} Chunk;

typedef struct Chunks {
    Chunk  *chunks;
    size_t size;
    size_t cap;
} Chunks;

// Loader.
int    load(FILE *Stream, Chunk *chunk);
int    load_all(FILE *Stream, Chunks *chunks);

// dumpers.
int    chunk_dump(FILE *Stream, Chunk *chunk);
int    chunks_dump(FILE *Stream, Chunks *chunks);

// Allocators. 
Chunk  allocChunk(size_t cap);
Chunks allocChunks(size_t cap, size_t amount);


#endif // CHUNK_H
