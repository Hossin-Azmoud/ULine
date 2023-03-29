#include "chunk.h"

// TODO int    load_all(FILE *Stream, Chunks *chunks); 
// TODO Chunks AllocChunks(size_t cap, size_t amount); 
// TODO int    chunks_dump(FILE *Stream, Chunks *chunks); 

void NOT_IMPLEMENTED(void)
{
    printf("%s IS NOT NOT IMPLEMENTED", __func__);

} 
   
Chunks *load_all(FILE *Stream)
{  	
	// Allocate mem for the whole file.
	// The size of the whole file.
	
	long size = get_file_size(Stream);
	printf("full size: %lu\n", size);
	
	// The remaining size if we devide by 1024 byte.
	size_t rem = (size % CHUNK_SIZE);

	// The qoutient
	size_t q = (size - rem);
	
	// The amount of chunks we need to allocate.
	size_t chunkAmount = (q / CHUNK_SIZE) + ((rem != 0) ? 1 : 0);
		
	printf("Alloc chunks: %zu\n", chunkAmount);
	Chunks *chunks = AllocChunks(0, chunkAmount);
	
	int code;

	for(size_t i = 0; i < chunkAmount; i++)
	{	
		code = load(Stream, chunks->items + i);
		
		// if chunks.size == chunks.cap then the memory that was perviously allocated is full.
		// load returns the amount of bytes it read so, it is like if there is nothing to read, exiting the loop is the most responsible to do.
		
		if(code == 0) 
		{
			break;
		}
		
		chunks->size++; //

	}


	return chunks;
}

int chunks_dump(FILE *Stream, Chunks *chunks)
{  

	
    if(Stream == NULL)
    {
		return 1;
    }    
	
	printf("(size: %zu)\n", chunks->size);

	for(size_t i = 0; i < chunks->size; i++)
	{
		// TODO: Last chunk hangs here. it does not get written.
		Chunk *chunk = (chunks->items + i);
    	fwrite(chunk->bytes, 1, chunk->size, Stream);

	}

	return 0;
}

/*

Chunks AllocChunks(size_t cap, size_t amount)
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

    Chunk *chunk = AllocChunk(0);
    
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

Chunk *AllocChunk(size_t cap)
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

Chunks *AllocChunks(size_t cap, size_t amount)
{
	// So chunks is empty from garbage values
	
	Chunks *chunks = calloc(1, sizeof(Chunks));	
	chunks->cap   = amount;

    if(cap == 0) cap = CHUNK_SIZE;
    
    chunks->items = (void *) malloc(sizeof(Chunk) * amount);
    

    for(; amount > 0; amount--)
    {
        Chunk *C = chunks->items + (amount - 1);

		(C)->bytes = calloc(cap, sizeof(void));
		(C)->cap   = cap;
		(C)->size  = 0;
		// INFO: BUG :(
		// chunks->size++;	
    }

    // Tested using malloc and memset and it does not set all the values. which is weird!
    // chunk->bytes = malloc(cap);
    // memset(chunk->bytes, 0, chunk->cap);
    
    return chunks;

}
