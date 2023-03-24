#ifndef ULINE_IMPL
#define ULINE_IMPL

#define DEFAULT_LINE_CAP   32 // Buffer to contain line.
#define DEFAULT_LINE_COUNT 32 // Buffer to contain line.
#define EOB              '\0'
#define EOL              '\n'

typedef struct Line {
    char      *content;
    size_t    size;
    size_t    index;
    size_t    cap;
} Line;

// TODO: TEST.

// Readers.
void    line_log(Line *l);
int	read_line_from_stream(FILE *Stream, Line *l);
int     read_lines_from_stream(FILE *Stream, Line *Lines, size_t *read, size_t end);
Line    *read_lines_from_stream_dyn(FILE *Stream, size_t *read);

// Writers.
size_t  write_into_line(Line *l, char *buff);
int 	dump_line_into_stream(FILE *Stream, Line *l);

size_t  Uline_write_buff_into(Line *l, char *data);
bool    Uline_write_byte_into(Line *l, char byte, bool term);

// Reader + writer.
size_t  concat(Line *src, Line *dst);

// Util
int  iota(size_t i, char *a); // converts Int -> ascii
void memcheck(Line *l, size_t offset, bool movebuff); // check if the allocated mem in Line->content
Line AllocLine(size_t capacity);
void terminate(char *buff, size_t index);

#endif // ULINE_IMPL

