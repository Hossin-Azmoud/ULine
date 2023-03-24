#include "./ULine.c"
#define IN "OUT/test.txt"

int main(void)
{
    Line src = {
	.content="Hello",
	.size=5,
    }; 

    Line dst = {
	.content=" World",
	.size=6,
    };

    concat(&src, &dst);
    printf("%s", src.content);
    
    Line dst_ = {
	.content=" WeZDS",
	.size=6,
    };

    concat(&src, &dst_);
    printf("%s", src.content);
    
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
