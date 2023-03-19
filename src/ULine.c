#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 250
#define NL              '\n'
#define CHUNK_SIZE      100

typedef struct ULine {
    char      lineBuffer[MAX_LINE_LENGTH];
    size_t    size;
    size_t    index;
} ULine;

/* ------------ Definition ------------------ */

// Readers.
void    ULine_log(ULine *l);
int 	ULine_read_line_from_stream(FILE *Stream, ULine *l);
int     ULine_read_lines_from_stream(FILE *Stream, ULine *Lines, size_t *read);

// Writers.
size_t  ULine_write(ULine *l, char *buff);
int 	ULine_dump_line_into_stream(FILE *Stream, ULine *l);

// Reader + writer.
size_t  ULine_concat(ULine *src, ULine *dst);

// Util
int ULine_iota(size_t i, char *a);

/* ------------------------------------------- */

/* ------------ Implementation ------------------ */
size_t  ULine_concat(ULine *src, ULine *dst)
{
    strcat(src->lineBuffer, dst->lineBuffer);
    src->size += dst->size;
    return src->size;
}

size_t ULine_write(ULine *l, char *buff) {
    size_t length = strlen(buff);

    assert((length < MAX_LINE_LENGTH) && "SIZE OF THE BUFFER IS BIGGER THAN 512 BYTES!");
    size_t it = 0;
    
    for(; it < length; it++)
    {
	l->lineBuffer[l->size++] = buff[it];
    }

    return l->size;
}

void ULine_log(ULine *l) {
    printf("Line: %s\n", l->lineBuffer);
    printf("Size: %zu\n", l->size);
}
// Read Line By line.
int ULine_read_line_from_stream(FILE *Stream, ULine *l)
{
    l->size = 0;
    int c;
    
    while(((c = fgetc(Stream)) != EOF) && ((char)c != NL)){
	l->lineBuffer[l->size++] = (char)c;
    }

    l->lineBuffer[l->size++] = NL;
    
    return c;
}

int ULine_dump_line_into_stream(FILE *Stream, ULine *l) {
    if(Stream != NULL){
	fprintf(Stream, l->lineBuffer);
	return 0;
    }
    
    return 1;
}

int ULine_iota(size_t i, char *a)
{
    int length = snprintf(NULL, 0, "%zu", i);
    snprintf(a, length + 1, "%zu", i);
    return length;
}

// read an array of lines. but the problem here you need to allocate mem for the lines that you want to read. then assign the mem to *Lines so they can be stored there.. 
int ULine_read_lines_from_stream(FILE *Stream, ULine *Lines, size_t *read)
{
    size_t Count = 0;
    ULine  tmp 	 = { 0 };
    int c;

    while((c = ULine_read_line_from_stream(Stream, &tmp)) != EOF) 
    {
	// Assign the line.
	tmp.index   = Count;
	Lines[Count] = tmp;
	Count++; // Next.
    }
    
    *read = Count;
    return c;
}

/* ------------------------------------------- */

