#include "ULine.h"

void report_read(Line line)
{
    printf("---------------------------------------\n");
    
    printf("READ: %zu\n", line.size);
    
    printf("---------------------------------------\n");
}


size_t concat(Line *src, Line *dst) 
{
    size_t s = Uline_write_buff_into(src, dst->content);
    return s;
}

Line AllocLine(size_t capacity)
{
    if(capacity == 0){
	capacity = DEFAULT_LINE_CAP;
    }

    Line line = { 0 };
    char *tmp    = (char *) malloc(capacity + 1);
    line.size    = 0;
    line.cap     = capacity;
    line.content = tmp;

    return line;
}

void memcheck_rea(Line *l, size_t offset, bool movebuff)
{
    if(!movebuff)
    {
	*l = AllocLine(l->size + offset);
	return;
    }

    if(l->cap < (l->size + offset)) {
	size_t bytes_to_Alloc = (l->cap + DEFAULT_LINE_CAP);
	l->content            = (char *) realloc(l->content, bytes_to_Alloc);
	l->cap += DEFAULT_LINE_CAP;
    }
}

void memcheck(Line *l, size_t offset, bool movebuff) {
    
    if(!movebuff)
    {
	*l = AllocLine(l->size + offset);
	return;
    }

    if(l->cap < (l->size + offset)) {
	
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

void terminate(char *buff, size_t index)
{
    buff[index] = EOB;
}

bool Uline_write_byte_into(Line *l, char byte, bool term)
{

    memcheck(l, 1, true); // Check if buffer is enough for the incoming bytes.
    l->content[l->size] = byte;
    
    l->size++;
    if(term) terminate(l->content, l->size);
    return true;
}

size_t  Uline_write_buff_into(Line *l, char *data)
{
    size_t n = strlen(data);
    
    memcheck(l, n, true); // Well it overflow if we add n bytes. if yes then reallocate.

    if(n > 0)
    {
	// DEFAULT_LINE_CAP
	for(size_t j = 0; j < n; j++)
	{
	    l->content[l->size++] = data[j];
	}

	terminate(l->content, l->size);
    }

    return l->size;
}

size_t write_into_line(Line *l, char *buff) {
    
    size_t length = strlen(buff);
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
    printf("Current Capacity: %zu\n", l->cap);
}

// Read Line By line.
int read_line_from_stream(FILE *Stream, Line *l)
{

    int c;
    while(((c = fgetc(Stream)) != EOF) && ((char) c != EOL)){
	Uline_write_byte_into(l, (char) c, false);
    }
    
    terminate(l->content, l->size);
    return c;
}
/*
size_t refill(Line *line,char *buff)
{
size_t n = strlen(buff);
    memcheck();
    return 
}
*/
int dump_line_into_stream(FILE *Stream, Line *l) {
    
    if(Stream != NULL){
	fprintf(Stream, l->content);
	return 0;
    }
    
    return 1;
}

int iota(int i, char *a)
{
    int length = snprintf(NULL, 0, "%i", i);
    snprintf(a, length + 1, "%i", i);
    terminate(a, length);
    return length;
}


int  fota(float f, char *a)
{
    int length = snprintf(NULL, 0, "%f", f);
    snprintf(a, length + 1, "%f", f);
    terminate(a, length);
    return length;
}
// converts Int -> ascii
// read an array of lines. but the problem here you need to allocate mem for the lines that you want to read. then assign the mem to *Lines so they can be stored there.. 
int read_lines_from_stream(FILE *Stream, Line *Lines, size_t *read, size_t end)
{
    size_t Count = 0;
    Line  tmp	 = { 0 };
    int c;

    while((c = read_line_from_stream(Stream, &tmp)) != EOF) {
	// Assign the line.
	
	tmp.index    = Count;
	Lines[Count++] = tmp;
	if(Count == end) break;
    }
    
    *read = Count;
    return c;
}

Line *read_lines_from_stream_dyn(FILE *Stream, size_t *read)
{ 
    size_t s        = sizeof(Line) * DEFAULT_LINE_COUNT;
    
    size_t Count    = 0;
    int c;

    Line   *Lines   = (Line *) malloc(s); // Allocate 32 Line.
    Line  tmp	    = { 0 };

    while((c = read_line_from_stream(Stream, &tmp)) != EOF) {
	// Assign the line.
	if(Count == (s / sizeof(Line))) {
	    // The lines buff is full, realloc.
	    s += sizeof(Line) * DEFAULT_LINE_COUNT;
	    Lines = (Line *) realloc(Lines, s);
	}

	tmp.index      = Count;
	Lines[Count++] = tmp;
    }
    
    *read = Count;
    
    return Lines;
}

Lines AllocLines(size_t capacity, size_t count)
{
    Lines lines = { 0 };
    lines.cap   = count;
    lines.line_list = malloc(sizeof(Line) * count);
    
    for(;count > 0; count--)
    {
	lines.line_list[count - 1] = AllocLine(capacity);
    }

    return lines;
}

int dump_lines(FILE *Stream, Lines *lines)
{
    if(Stream == NULL)
    {
		return 1;
    }
    
    for(size_t i = 0; i < lines->size; i++)
    {
		dump_line_into_stream(Stream, &(lines->line_list[i]));    
	}
	
	return 0;
}

Lines read_lines(FILE *Stream, size_t amount)
{
    int code    = 0;
    Lines lines = AllocLines(DEFAULT_LINE_CAP, amount);
    lines.cap   = amount;
    
    printf("(size: %zu), (Am: %zu)\n", lines.size, amount);

    for(; lines.size < amount; lines.size++)
    {
	if(code == EOF)
	{
	    printf("EOF (%i) == (%i) ", code, EOF);
	    break;
	}

	Line tmp = AllocLine(DEFAULT_LINE_CAP);
	code = read_line_from_stream(Stream, &tmp);
	lines.line_list[lines.size] = tmp;
    }
    
    printf("(size: %zu), (Am: %zu)\n", lines.size, amount);
    
    return lines;
}
