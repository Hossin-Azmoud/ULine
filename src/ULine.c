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
} ULine;

void    ULine_info(ULine *l);
size_t  ULine_append(ULine *l, char *buff);
int 	ULineReadFromStream(FILE *Stream, ULine *l);
int 	ULineDumpLine(FILE *Stream, ULine *l);
int     convNum(size_t Num, ULine *l);
size_t  Linecat(ULine *src, ULine *dst);
int     ReadLines(FILE *Stream, ULine *Lines, size_t *readCounter);
int     ReadLinesNumbered(FILE *Stream, ULine *Lines, char *sep, size_t *readCounter);

size_t Linecat(ULine *src, ULine *dst)
{
    strcat(src->lineBuffer, dst->lineBuffer);
    src->size += dst->size;
    return src->size;
}

size_t ULine_append(ULine *l, char *buff) {
    size_t length = strlen(buff);

    assert((length < MAX_LINE_LENGTH) && "SIZE OF THE BUFFER IS BIGGER THAN 512 BYTES!");
    size_t it = 0;
    
    for(; it < length; it++)
    {
	l->lineBuffer[l->size++] = buff[it];
    }

    return l->size;
}

void ULine_info(ULine *l) {
    printf("Line: %s\n", l->lineBuffer);
    printf("Size: %zu\n", l->size);
}
// Read Line By line.
int ULineReadFromStream(FILE *Stream, ULine *l)
{
    l->size = 0;
    int c;

    while(((c = fgetc(Stream)) != EOF) && ((char)c != NL)){
	l->lineBuffer[l->size++] = (char)c;
    }
    
    l->lineBuffer[l->size++] = NL;
    
    return c;
}

int ULineDumpLine(FILE *Stream, ULine *l) {
    if(Stream != NULL){
	fprintf(Stream, l->lineBuffer);
	return 0;
    }
    
    return 1;
}

int convNum(size_t Num, ULine *l)
{
    int length = snprintf(NULL, 0, "%zu", Num);
    snprintf(&(l->lineBuffer[0]), length + 1, "%zu", Num);
    l->size += length;
    return length;
}

// read an array of lines. but the problem here you need to allocate mem for the lines that you want to read. then assign the mem to *Lines so they can be stored there.. 
int ReadLinesNumbered(FILE *Stream, ULine *Lines, char *sep, size_t *readCounter)
{
    if(*readCounter != 0)
    {
	*readCounter = 0;
    }

    ULine  tmp 	 = { 0 };
    int c;
    size_t sep_size = strlen(sep);
    
    while((c = ULineReadFromStream(Stream, &tmp)) != EOF) 
    {
	ULine  line  = { 0 };		
	//printf("Read loop!\n");
	convNum(*readCounter, &line); // Convert the number to its char repr.
	
	for(size_t j = 0; j < sep_size ; j++){
	    line.lineBuffer[line.size++] = sep[j]; // Add sep.
	}
	
	Linecat(&line, &tmp);
	// Assign the line.
	Lines[*readCounter] = line;
	
	(*readCounter)++; // Next.
    }


    return c;
}

int ReadLines(FILE *Stream, ULine *Lines, size_t *readCounter)
{
    if(*readCounter != 0) *readCounter = 0;

    ULine  tmp 	 = { 0 };
    int c = 0;

    while((c = ULineReadFromStream(Stream, &tmp)) != EOF) 
    {
	Lines[(*readCounter)++] = tmp;
    }
    
    return c;
}

