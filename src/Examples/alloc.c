#include "../chunk.h"
#include "../ULine.h"


/*

Chunk   *allocChunk(size_t cap); // Alloc a chunk with capacity.
Chunks  *allocChunks(size_t cap, size_t amount); // Alloc amount-chunks with the cap.
Line    *AllocLine(size_t capacity); // Allocate line struct.
Lines   *AllocLines(size_t capacity, size_t count); // allocate count-lines in the Lines struct with capacity.

*/

void ChunkAllocation_Example()
{
	// Allocate default chunk size: 1kb. if it is not 0 then it allocates the number you specify.
	Chunk *chunk = AllocChunk(0);
	Chunks  *chunks = AllocChunks(1024, 2); 
	// Allocates 2 lines with 1kb of capacity each.
	//
		
	free(chunk);
	free(chunks);
}

void LineAllocation_Example()
{
	// AllocLines(line_Buffer_size, Line_count);
	// If line_Buffer_size == 0 then we allocate 32 byte buffer for each line.
	// else we allocate it normally. and if Line_count
	
	Line *line = AllocLine(100); // Allocate one line with this capacity. if cap is 0 then it allocated the default which is 64							 //
	Lines *lines = AllocLines(100, 4); // Allocates 4 lines with cap of 100 characters, if both are 0 then we allocate 32 lines with cap of 64.
	free(line);
	free(lines);

}



int main()
{
	printf("Hello, World!\n");
	ChunkAllocation_Example();
	LineAllocation_Example();
	return 0;
}




