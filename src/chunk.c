#include "chunk.h"

// TODO int    load_all(FILE *Stream, Chunks *chunks); 
// TODO Chunks allocChunks(size_t cap, size_t amount); 
// TODO int    chunks_dump(FILE *Stream, Chunks *chunks); 

void NOT_IMPLEMENTED(void)
{
    printf("%s IS NOT NOT IMPLEMENTED", __func__);

} 
   
int    load_all(FILE *Stream, Chunks *chunks)
{  
    NOT_IMPLEMENTED();
    return 0;  
}  

int    chunks_dump(FILE *Stream, Chunks *chunks)
{  
    NOT_IMPLEMENTED();
    return 0;  
}
       
/*
Chunks allocChunks(size_t cap, size_t amount)
{  
    NOT_IMPLEMENTED();
    return 0;  
}  
 */ 
       
  

int load(FILE *Stream, Chunk *chunk)
{
   int byte; 
   while((byte = fgetc(Stream) != EOF) && chunk->size < chunk->cap) 
   {
	chunk->bytes[chunk->size++];		
   }

   return byte;
}

int chunk_dump(FILE *Stream, Chunk *chunk)
{
    if(Stream == NULL)
    {
	return 1;
    }

    fprintf(Stream, chunk->bytes);

    return 0;
}

Chunk allocChunk(size_t cap)
{
    if(cap == 0)
    {
	cap = CHUNK_SIZE;
    }

    Chunk chunk = { 0 };
    chunk.cap   = cap;
    chunk.bytes = (int *) malloc(sizeof(int) * cap);
    return chunk;
}


