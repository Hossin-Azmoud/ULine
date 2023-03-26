# ULine
A simple lines lib in C.

# Structs And Constants

My Main strcuture in this project is a Line struct:
```C
 typedef struct Line {
    char      *content;
    size_t    size;
    size_t    index;
    size_t    cap;
} Line;
```
it contains some usefull props like the size, the capacity of its content (How much mem it allocated in order to store the line), the index (index - 1 is the line number. just incase.) and lastly the content which is the actual text it stores.
```C
#define DEFAULT_LINE_CAP   32 // Buffer to contain line.
#define DEFAULT_LINE_COUNT 32 // Buffer to contain line.
#define EOB              '\0'
#define EOL              '\n'
```
- `EOB`: the termination char for the Line struct.
- `EOL`: the end of a line, I use it to know if I read the whhole line.
- `DEFAULT_LINE_CAP` set to 32, and it is used to dynamically allocate mem for the Line->content buffer. because if it is full we reallocate using the function `memcheck`
- `DEFAULT_LINE_COUNT` set to 32, and it is used as a primary size for a Line[], and also it is the offset when we allocate more mem to read more line into our lineArray. check function `read_lines_from_stream_dyn`

#### Other structures

```C
 typedef struct Lines {
    Line      *line_list;
    size_t    size;
    size_t    cap;
} Lines;
```
I made this one just to encapsulate the first Line struct.. 

# Functions

## Readers.

- `ULine_log`: Log the information about a line structure.
- `ULine_read_line_from_stream`: Read ULine from a given stream.
- `read_lines_from_stream`: Read into gives Lines array until EOF.
- `read_lines`: reads a specific amount of lines and returns the Line struct back.!
- `read_lines_from_stream_dyn`: dynamic line loader. specify only a pointer to size_t to get the size of the array that will be returned!

## Writers.
- `ULine_write`: Writes given buffer into a ULine struct.
- `dump_line_into_stream`: Writes given line into a stream.
- `dump_lines`: dumps struct lines into a file stream.
   
## Reader + writer.
- `ULine_concat`: get src ULine and dst ULine and appends dst into the src.
   
## Util
- `iota`: gets an unsigned int and converts it into its ascii repr then writing it to the given buffer.
- `fota`: similar to iota but gets a float as input. 
- `terminate`: terminate the buffer in the given index.
- `AllocLine`: allocate new empty line. with a given capacity.
- `memcheck`: checks if the line is enough for its size + offset. if not we reallocate a new line using malloc.
- `memcheck_rea`: similar to `memcheck` but uses realloc to expand the line content buffer.
L   
    
