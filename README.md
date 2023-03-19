# ULine
A simple lines lib in C.

# Functions


## Readers.

- `ULine_log`: Log the information about a line structure.
- `ULine_read_line_from_stream`: Read ULine from a given stream.
- `ULine_read_lines_from_stream`: Read Lines until EOF.

## Writers.
`ULine_write`: Writes given buffer into a ULine struct.
`ULine_dump_line_into_stream`: Writes given line into a stream.

## Reader + writer.
`ULine_concat`: get src ULine and dst ULine and appends dst into the src.

## Util
`ULine_iota`: gets an unsigned int and converts it into its ascii repr then writing it to the given buffer.

