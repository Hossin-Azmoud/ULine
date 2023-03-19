#include "./ULine.c"
#include <stdio.h>

int main(void)
{
    FILE   *fp      = fopen("./test.txt", "r");
    FILE   *out     = fopen("./o.txt", "w+");
    size_t linecount = 0;
    ULine  lines[100];
    
    printf("%zu kb allocated.\n", (sizeof lines * 100) / 1024);

    for(size_t i = 0; i < 100; i++)
    {
	if(lines[i].size != 0)
	{
	    lines[i].size = 0;
	}
	// printf("%p  |  %i  |  %p\n", &lines[i], lines[i].size, lines[i].lineBuffer);
    }

    if(fp == NULL) {
	printf("File could not be open :)");
	fclose(fp);
	return 1;
    }
        
    // Reading all the line with Numbers
    int c = ReadLinesNumbered(fp, lines, " -> ", &linecount);
    printf("read %zu lines !!\n", linecount);
    
    // printing.
    
    for(; linecount > 0; linecount--)
    {
	ULineDumpLine(out, &lines[linecount - 1]);
    }
   
//    free(lines);
    fclose(fp);
    fclose(out);
    return 0;
}
