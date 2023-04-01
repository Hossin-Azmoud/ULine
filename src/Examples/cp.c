#include "../chunk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

#include <unistd.h>
#include <ctype.h>

#define MAX 512

typedef struct Args {
	char *file;
	char *dst_out;
	FILE *in;
	FILE *out;
} Args;

void TCopy(Args *a);
void Copy(Args *a);

int isDir(const char* p);
bool file_exists(const char *fpath);
bool dir_exists(const char *folder);
void CloseFiles(Args *a);

char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
void replace(char *path, char replacement, char replacer);

void Error(void);
void help(void);
size_t max(size_t a, size_t b);

char *GetFileName(char *path);

void setIO(Args *a);

Args *setArgs(const char *file, const char *dst);
Args *alloc(size_t cap);

int main(int argc, const char *argv[])
{
	if(argc < 3)
	{
		help();
		return 0;
	}

	Args *a = setArgs(argv[1], argv[2]);

	a->file = trim(a->file);
	
	a->dst_out = trim(a->dst_out);
	
	setIO(a);
	
	Copy(a);
	
	CloseFiles(a);
	return 0;
}

void TCopy(Args *a)
{
	printf("%s -> %s (COPYING...)\n", a->file, a->dst_out);
}

int isDir(const char* p)
{
    struct stat path;
    stat(p, &path);
	return S_ISDIR(path.st_mode);
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

bool file_exists(const char *fpath)
{
    struct stat buffer;
    return stat(fpath, &buffer) == 0 ? true : false;
}

bool dir_exists(const char *folder)
{
	struct stat sb;
	return (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void Error(void)
{
	perror("ERROR: ");
	printf("Error code: %i\n", errno);
	exit(1);
}

void help()
{
	printf("USAGE: cp src<path> dst<path>\n");
	printf("DESCRIPTION: Copies file from its source to dst path.\n");

}

size_t max(size_t a, size_t b)
{	
	if(a > b)
	{
		return a;
	}

	return b;
}

Args *alloc(size_t cap)
{
	Args *a    = malloc(sizeof(Args));
	a->file    = malloc(cap);
	a->dst_out = malloc(cap);
	
	a->in = NULL;
	a->out = NULL;
	
	return a;
}

void CloseFiles(Args *a)
{
	if(a->in != NULL)  fclose(a->in);
	if(a->out != NULL) fclose(a->out);
}

void replace(char *path, char replacement, char replacer)
{
	size_t length = strlen(path);

	for(size_t it = 0; it < length; it++)
	{
		if(*(path + it) == replacement)
		{
			*(path + it) = replacer;
		}
	}

}

char *GetFileName(char *path)
{
	char *delim = "/";
	char *ptr  = strtok(path, delim);
	char *last = malloc(100);
	
	while (ptr != NULL)
	{		
		last = ptr;
		ptr  = strtok(NULL, delim);
	}

	return last;
}

void setIO(Args *a)
{
	replace(a->dst_out, '\\', '/');
	replace(a->file, '\\', '/');
	
	char *fileName = GetFileName(a->file);
	FILE *i;
	
	i = fopen(a->file, "rb");
	
	if(i == NULL) 
	{
		fprintf(stderr, "Could not open %s\n", a->file);
		Error();
	}
		
	a->in = i;

	FILE *o;

	if(dir_exists(a->dst_out))
	{
		printf("Directory.");
		if(a->dst_out[strlen(a->dst_out) - 1] != '/')
		{
			a->dst_out = strcat(a->dst_out, "/");
		}

		a->dst_out = strcat(a->dst_out, fileName);
	}

	
	o = fopen(a->dst_out, "wb");	
	
	if(o == NULL) {
	
		fprintf(stderr, "Could not open %s\n", a->dst_out);
		Error();
	}
	
	a->out = o;
}

Args *setArgs(const char *file, const char *dst)
{
	// Sets the arguments that the tool needs from the user.

	Args *a   = alloc(MAX);
	strcpy(a->file, file);	
	strcpy(a->dst_out, dst);
	return a;
}

void Copy(Args *a)
{    
    size_t read = 0;    
	int code = 1;

    Chunk *chunk = AllocChunk(0);
	if(chunk == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate chunk.");
		exit(1);
	}
   
    // Example copy the bytes from in to out.
    while((code != 0))
 // Not thee last chunk.
    {	
    	// Loading.
		chunk->size = 0;
		code = load(a->in, chunk);	
		
		// Dumping.
		chunk_dump(a->out, chunk);	
		read += chunk->size;
    }
		
	printf("Copies One file: %s -> %s\n", a->file, a->dst_out);
	printf("size: %zu\n", read);
   
	free(chunk);
}







