#include "../ULine.h"

void checkl(Line *line)
{
    printf("CAP: %zu\n", line->cap);
    printf("SIZE: %zu\n", line->size);
    printf("mem block pointer: %p\n", line->content);
}

void check(char *a, int len)
{
    printf("degit count: %i\n", len);
    
	int i = 0;
	for(; i < len; i++)
    {
		if(i == 0)
			printf("%c ", a[i]);
		if(i > 0 && i < len - 1)
			printf(" %c ", a[i]);
		if(i == len - 1)
			printf(" %c\n", a[i]);
    }
    
    if(a[i] == EOB)
    {
		printf("terminated: true\n");
		return;

	}

	printf("terminated: false\n");
}

int main(void)
{
    // ---------------Int to ascci conversion.-------------------------
    char a[10];
    int length;
    length = iota(666, a); // 666 -> "666\0"
    // printf("%s\n", a);
    check(a, length);
    
    length = iota(66666666, a); // 66666666 -> "66666666\0"
    // printf("%s\n", a);
    check(a, length);

    length = iota(-666, a);    // -666 -> "-666\0"
    // printf("%s\n", a);
    check(a, length);

    length = fota(0.5, a); // .5 -> "0.500000\0"
    // printf("%s\n", a);
    check(a, length);
    
    // Line allocation.
    
    Line *l = AllocLine(20); // Allocate A line struct that can fit 20 charcters.
    checkl(l);
    l = AllocLine(100); // Allocate line with capacity of 100 characters.
    checkl(l);
    l = AllocLine(0); // Allocate line with the defualt line cap: 32 
    
	checkl(l);
    
    return 0;
}

/*
void memcheck(Line *l, size_t offset, bool movebuff); // check if the allocated mem in Line->content

Line  AllocLine(size_t capacity);
Lines AllocLines(size_t capacity, size_t count);
void  terminate(char *buff, size_t index);
*/

