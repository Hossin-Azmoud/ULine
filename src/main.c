#include "ULine.c"
#include "chunk.c"

#define IN "OUT/t.jpg"
#define OUT "OUT/t-1.jpg"

int main(void)
{
    FILE   *in = fopen(IN, "rb");
    FILE   *out = fopen(OUT, "wb");
    int    code;
    size_t size = 0;
    Chunk chunk = allocChunk(0);
    
    if((in == NULL) || (out == NULL))
    {
	fclose(in);
	fclose(out);
	return 1;
    }

    // Example copy the bytes from in to out.   
    while((code = load(in, &chunk)) != EOF && chunk.size > 0)
    {
    
	chunk_dump(out, &chunk);
	size += chunk.size;
	printf("wrote %zu\n", chunk.size);
    }

    printf("coppied: %zu bytes -> %s\n", size, OUT); 
    
    fclose(in);
    fclose(out);
    return  0;
}


