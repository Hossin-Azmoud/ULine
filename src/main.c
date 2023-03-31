#include "ULine.h"
#include "chunk.h"
#include <math.h>
#define IN    "OUT/t.jpg"
#define OUT   "OUT/t-1.jpg"
#define TEXT  "OUT/test.txt"
#define TEXTO "OUT/test-1.txt"

/*
	if(k->size > 0) printf("Success:\n");
	if(k->size == 0) {
		printf("failure:\n");
		return 1;
	};
	
	size_t Alloc = 0;

	for(size_t i = 0; i < k->size; i++)
	{
		Chunk *C = (k->items + i);
		
		// Because the bytes are *void then I think I need to convert them into a *char before trying to print(bytes).
		printf("[%zu] ", i);

		for(size_t j = 0; j < (C->size); j++)
		{:
			// Test if I can convert void into a char character. 			// I can not :(
			bool showstat = false;

			void *byte_as_void = ((C)->bytes + j);
			char byte          = (char) *(byte_as_void);
			
			if(showstat)
			{
				printf("sizeof(void) = %zu\n", sizeof(void));
				printf("sizeof(char) = %zu\n", sizeof(char));
				continue;
			}

			printf("|%c|", byte);

		}

		printf("[%zu] size: %zu\n", i, (C)->size);
		printf("[%zu] capacity: %zu\n", i, (C)->cap);

		printf("------------------------------------\n");
		Alloc += C->cap;
	}	

	printf("Total Allocated mem: %zu\n", Alloc); 
*/

int Copy(char *i, char *o);

void callback(Line *line)
{
	printf("content: %s\n", line->content);
	printf("SIZE: %zu\n", line->size);
}

// b KB mb gb 
enum UNITS {
	BYTE = 0,
	KB   = 666,
	MB,
	GB
} UNITS;


int convert(size_t Number, enum UNITS unit)
{
	return pow(1000, unit) * Number;
}

void test_conv()
{
	printf("%i\n", 10 ^ 10);

	int kb_in_bytes = convert(1, KB);
	printf("1kb -> %i byte\n", kb_in_bytes);
	
	int mb_in_bytes = convert(1, MB);

	printf("1mb -> %i byte\n", mb_in_bytes);
	
	int GB_in_bytes = convert(1, GB);
	
	printf("1gb -> %i byte\n", GB_in_bytes);
}

int main()
{	
	// Open files.
	Lines *lines = AllocLines(1000, 4); // 4 | 1000 bytes 4kb.

	// Fill lines.
	
	FillLines(lines, 'A');
	
	Lines_map(lines, callback);
	
	return 0;
}


int Copy(char *i, char *o)
{
    FILE   *in = fopen(i, "rb");
    FILE   *out = fopen(o, "wb");
    
    size_t read = 0;
    
	int code = 1;

    Chunk *chunk = AllocChunk(0);

    if((in == NULL) || (out == NULL))
    {
		fclose(in);
		fclose(out);
		free(chunk);
		return 1;
    }
    
    // Example copy the bytes from in to out.
    while((code != 0))
 // Not thee last chunk.
    {	
    	// Loading.
		chunk->size = 0;
		code = load(in, chunk);	
		
		// Dumping.
		chunk_dump(out, chunk);	
		read += chunk->size;

    }
    
    report_usage(chunk);

    fclose(in);
    fclose(out);
    free(chunk);

    return  0;

}

int main2(void)
{

    FILE   *in = fopen(IN, "rb");
    FILE   *out = fopen(OUT, "wb");
    int    code;
    size_t size = 0;
    Chunk *chunk = AllocChunk(0);
    
    if((in == NULL) || (out == NULL) || (chunk == NULL))
    {
		fclose(in);
		fclose(out);
		return 1;
    }
    
    // Doc.
    // Example copy the bytes from in to out.   
    while((code = load(in, chunk)) != EOF && chunk->size > 0)
    {
		chunk_dump(out, chunk);
		size += chunk->size;
    }
    
    printf("coppied: %zu bytes -> %s\n", size, OUT); 
    
    fclose(in);
    fclose(out);
    free(chunk);

    return  0;
}


