#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ULine.h"

// TODO: Make dynamic lines. DLine
// TODO: Implement dynamic lines DLine funcs to read/srite to the line
// TODO: Implement
size_t concat(Line *src, Line *dst)
{
    size_t s = Uline_write_buff_into(src, dst->content);
    return s;
}

void memcheck(Line *l, size_t offset)
{
    if(l->cap < (l->size + offset))
    {
	size_t i              = 0;
	size_t bytes_to_Alloc = (l->cap + DEFAULT_LINE_CAP);
	char *tmp             = (char *) malloc(bytes_to_Alloc);

	
	if(l->size > 0) {
	    for(; i < l->size; i++)
	    {
		tmp[i] = l->content[i];
	    }
	}

	l->content = tmp;
	l->cap += DEFAULT_LINE_CAP;
    }
}

bool Uline_write_byte_into(Line *l, char byte)
{
	/*T*/
	/**/
    
    memcheck(l, 1); // Check if buffer is enough for the incoming bytes.
    l->content[l->size]     = byte;
    l->content[l->size + 1] = '\0';
    
    return true;
}

size_t  Uline_write_buff_into(Line *l, char *data)
{
    size_t n = strlen(data);
    
    memcheck(l, n);

    if(n > 0)
    {
	// DEFAULT_LINE_CAP
	for(size_t j = 0; j < n; j++)
	{
	    l->content[l->size++] = data[j];
	}
	
	l->content[l->size]     = '\0';

    }

    return l->size;
}

size_t write_into_line(Line *l, char *buff) {
    size_t length = strlen(buff);

    assert((length < DEFAULT_LINE_CAP) && "SIZE OF THE BUFFER IS BIGGER THAN 512 BYTES!");
    size_t it = 0;
    
    for(; it < length; it++)
    {
	l->content[l->size++] = buff[it];
    }

    return l->size;
}



void line_log(Line *l) {
    printf("Line: %s\n", l->content);
    printf("Size: %zu\n", l->size);
}
// Read Line By line.
int read_line_from_stream(FILE *Stream, Line *l)
{
    l->size = 0;
    int c;
    
    while(((c = fgetc(Stream)) != EOF) && ((char)c != NL)){
	l->content[l->size++] = (char)c;
    }

    l->content[l->size++] = NL;
    
    return c;
}

int dump_line_into_stream(FILE *Stream, Line *l) {
    if(Stream != NULL){
	fprintf(Stream, l->content);
	return 0;
    }
    
    return 1;
}

int iota(size_t i, char *a)
{
    int length = snprintf(NULL, 0, "%zu", i);
    snprintf(a, length + 1, "%zu", i);
    return length;
}

// read an array of lines. but the problem here you need to allocate mem for the lines that you want to read. then assign the mem to *Lines so they can be stored there.. 
int read_lines_from_stream(FILE *Stream, Line *Lines, size_t *read)
{
    size_t Count = 0;
    Line  tmp 	 = { 0 };
    int c;

    while((c = read_line_from_stream(Stream, &tmp)) != EOF) 
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

