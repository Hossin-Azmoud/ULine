#include "ULine.c"
#include "chunk.c"

#define IN   "OUT/t.jpg"
#define OUT  "OUT/t-1.jpg"
#define TEXT "OUT/test.txt"
#define TEXTO "OUT/test-1.txt"

int Copy(char *i, char *o);

int main()
{	

    Copy(IN, OUT);
    printf("finished!;\n");
    return 0;
}

int Copy(char *i, char *o)
{
    FILE   *in = fopen(i, "rb");
    FILE   *out = fopen(o, "wb");
    
    size_t read = 0;
    int code = 1;

    Chunk *chunk = allocChunk(0);

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
    Chunk *chunk = allocChunk(0);
    
    if((in == NULL) || (out == NULL) || (chunk == NULL))
    {
	fclose(in);
	fclose(out);
	return 1;
    }
    
    // Doc.
    printf("CAP: %zu\n", chunk->cap);
    printf("SIZE: %zu\n", chunk->size);
    printf("CHAR_: %zu\n", chunk->bytes);

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
