#include "../ULine.h"
#define IN "OUT/test.txt"
/* An example on how to read a Number of line n with func read_lines(fp, n).
 * if we reach EOF before reading n-Lines then we return the lines structure as is...
 * 
 * */
void trace(Lines lines)
{
    printf("ALLOCATION: %zu\n", lines.cap);
    printf("LINES: %zu\n", lines.size);
    
    for(size_t j = 0; j < lines.size; j++)
    {
		Line line = lines.line_list[j];
		printf("[%zu]:  s:%zu  c:%zu  t:%s\n", j, line.size, line.cap, line.content);
    }
}

int main(void)
{
    FILE *f   = fopen(IN, "r");

    if(f == NULL) {
	return 1;
    }

    Lines l = read_lines(f, 100);
    
    trace(l);
    
    fclose(f);
    return  0;
}
