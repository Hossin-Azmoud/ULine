
#include <errno.h>
#include "../ULine.c"
#define OUT "OUT/o.txt"
#define MAX 20

/* An example on how you can add characters to the lines using
 * Uline_write_byte_into(line_ref, char, termination_flag)
 * and how to dump the lines into a file using dump_line_into_stream(stream, line_ref)
 * also I have used a func to allocate me a line. which is AllocLine(size), size is the size of the line we are going to create.
 * 
 * */

int main()
{
    FILE *f      = fopen(OUT, "w+");    
    if(f == NULL)
    {
	printf("Error opening the file!");
	return 1;
    }
    size_t start = 48;
    size_t end   = 200;
    
    for(int i = 0; i < MAX; i++)
    {
	Line line = AllocLine(end - start);

	for(size_t j = start; j < end; j++)
	{
	     Uline_write_byte_into(
		&line,
		(char) j,
		(j == end - 1)
	    );
	}

	if(dump_line_into_stream(f, &line) == 0)
	{
	    printf("[*] wrote.. %d bytes into %s, with the index %zu\n", end - start, OUT, i);
	}
	
    }
    
    fclose(f);
    
    return 0;
}










