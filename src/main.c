#include "ULine.c"
#define IN "OUT/test.txt"

int main(void)
{
    FILE *f   = fopen(IN, "r");
    size_t length = 0;
    
    if(f == NULL)
    {
	printf("could not open the file %s\n", IN);
	fclose(f);
	return 1;
    }

    Line *lines = read_lines_from_stream_dyn(f, &length);
    
    printf("READ: %d\n", length);
    
    for(; length > 0; length--) printf("%s\n", lines[length - 1].content);

    

    fclose(f);
    return  0;
}

int Line_TEST(void)
{
    FILE   *fp      = fopen(IN, "r");
    FILE   *out     = fopen("OUT/o.txt", "w+");
    size_t linecount = 0;
    Line  lines[100];
    
    printf("%zu kb allocated.\n", (sizeof lines * 100) / 1024);

    for(size_t i = 0; i < 100; i++)
    {
	if(lines[i].size != 0)
	{
	    lines[i].size = 0;
	}
	// printf("%p  |  %i  |  %p\n", &lines[i], lines[i].size, lines[i].content);
    }

    if(fp == NULL) {
	printf("File could not be open :)");
	fclose(fp);
	return 1;
    }
        
    // Reading all the line with Numbers
    int c = read_lines_from_stream(fp, lines, &linecount);
    
    printf("read %zu lines !!\n", linecount);
    
    // printing.
    for(; linecount > 0; linecount--)
    {
	printf("%zu -> %s", lines[linecount - 1].index, lines[linecount - 1].content);
	// dump_line_into_stream(stdout, &lines[linecount - 1]);

    }
   
    fclose(fp);
    fclose(out);
    return 0;
}
