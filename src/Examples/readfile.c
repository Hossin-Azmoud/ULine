#include "../ULine.c"
#define IN "OUT/test.txt"

int READ_FILELINES(FILE *STREAM);
int READ_FILELINES_DYN(FILE *STREAM);
// void freset(FILE *STREAM);


int main(void)
{
    FILE *f   = fopen(IN, "r");
    
    if(f == NULL)
    {
    	printf("could not open the file %s\n", IN);
	fclose(f);
	return 1;
    }
    // Use the stream
    READ_FILELINES_DYN(f);
    READ_FILELINES(f);
    
    fclose(f);
    return 0;
}

int READ_FILELINES(FILE *STREAM)
{
    rewind(STREAM);
    size_t length = 0;
    Line lines[DEFAULT_LINE_COUNT];
    printf("Passed");
    // Read file content from Stream to LineArray. until you reach DEFAULT_LINE_COUNT then report how much was read with &length. 
    int c = read_lines_from_stream(STREAM, lines, &length, DEFAULT_LINE_COUNT);
    
    printf("[!] READ (READ_FILELINES): %d\n", length);
    return  0;
}


int READ_FILELINES_DYN(FILE *STREAM)
{
   
    rewind(STREAM); 
    size_t length = 0;
    // read lines until you finish, then return me the line count (length) and the actuall lines (*lines[length])
    Line *lines = read_lines_from_stream_dyn(STREAM, &length);
    printf("[!] READ (READ_FILELINES_DYN): %d\n", length);
    return  0;
}
