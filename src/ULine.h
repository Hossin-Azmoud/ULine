#ifndef ULINE_IMPL
#define ULINE_IMPL

#define DEFAULT_LINE_CAP 512 // Buffer to contain line.
#define NL              '\n'
#define CHUNK_SIZE      100

typedef struct Line {
    char      *content;
    size_t    size;
    size_t    index;
    size_t    cap;
} Line;

// Readers.
void    line_log(Line *l);
int 	read_line_from_stream(FILE *Stream, Line *l);
int     read_lines_from_stream(FILE *Stream, Line *Lines, size_t *read);

// Writers.
size_t  write_into_line(Line *l, char *buff);
int 	dump_line_into_stream(FILE *Stream, Line *l);
size_t  Uline_write_buff_into(Line *l, char *data);
bool    Uline_write_byte_into(Line *l, char byte);

// Reader + writer.
size_t  concat(Line *src, Line *dst);

// Util
int iota(size_t i, char *a);

#endif
