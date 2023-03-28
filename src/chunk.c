#include "chunk.h"

// TODO int    load_all(FILE *Stream, Chunks *chunks); 
// TODO Chunks allocChunks(size_t cap, size_t amount); 
// TODO int    chunks_dump(FILE *Stream, Chunks *chunks); 

void NOT_IMPLEMENTED(void)
{
    printf("%s IS NOT NOT IMPLEMENTED", __func__);

} 
   
int load_all(FILE *Stream, Chunks *chunks)
{  
    NOT_IMPLEMENTED();
    return 0;  
}  

int chunks_dump(FILE *Stream, Chunks *chunks)
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
       
  
long get_file_size(FILE *Stream) 
{
    fseek(Stream, 0L, SEEK_END);
    long size = ftell(Stream);
    fseek(Stream, 0L, SEEK_SET);
    return size;
}

Chunk load_chunk(FILE *Stream)
{    

    Chunk *chunk = allocChunk(0);
    
    size_t size = fread(chunk->bytes, 1, chunk->cap, Stream);
    chunk->size = size;

    return *chunk;
}

int load(FILE *Stream, Chunk *chunk)
{ 
    size_t s = fread(chunk->bytes, 1, chunk->cap, Stream);        
    chunk->size = s;
    
    return s;
}

int chunk_dump(FILE *Stream, Chunk *chunk)
{
    if(Stream == NULL)
    {
	return 1;
    }
    
    fwrite(chunk->bytes, 1, chunk->size, Stream);  
    return 0;
}

void report_usage(Chunk *chunk)
{
    printf("[!] Last chunk size: %zu\n", chunk->size);
    printf("[!] used chunk capacity: %zu\n", chunk->cap);
}

Chunk *allocChunk(size_t cap)
{
    if(cap == 0)
    {
	cap = CHUNK_SIZE;
    }

    Chunk *chunk = malloc(sizeof(Chunk));
    chunk->cap   = cap;
    chunk->size  = 0;
    
    chunk->bytes = calloc(cap, sizeof(void));
    // Tested using malloc and memset and it does not set all the values. which is weird!

    // chunk->bytes = malloc(cap);
    // memset(chunk->bytes, 0, chunk->cap);
    return chunk;

}
