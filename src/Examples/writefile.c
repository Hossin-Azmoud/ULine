
#include <errno.h>
#include "../ULine.c"
#define OUT "OUT/o.txt"
#define MAX 20
#define SEP '!'

void tell(char sep, char *msg)
{
    printf("[%c] %s", sep, msg);
}

int main()
{
    FILE *f      = fopen(OUT, "w+");    
    size_t start = 48;
    size_t end   = 200;
    tell(SEP, "Starting\n"); 
    
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
    
    return 0;
}










