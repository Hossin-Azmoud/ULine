#ifndef CHUNK_H
#define CHUNK_H
#define CHUNK_SIZE 1024
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Chunk {
    int *bytes;
    size_t size;
    size_t cap;
} Chunk;

int load(FILE *Stream, Chunk *chunk);
int chunk_dump(FILE *Stream, Chunk *chunk);
Chunk allocChunk(size_t cap);

#endif // CHUNK_H
