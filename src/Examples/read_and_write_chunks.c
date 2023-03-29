#include "../ULine.h"
#include "../chunk.h"

#define TEXT  "OUT/test.txt"
#define TEXTO "OUT/test-1.txt"

int main(){
	
	FILE *in = fopen(TEXT, "r");
	FILE *out = fopen(TEXTO, "w");
	
	if(in == NULL)
	{
		fclose(in);
		fclose(out);
		return 1;		
	}

	// Get the chunks from in.
	Chunks *k =  load_all(in);

	// Dump the chunks to out.
	int code = chunks_dump(out, k);		
	
	// 0 on success and 1 on failure.
	
	if(code == 0) 
	{
		printf("%s -> %s\n", TEXT, TEXTO);
	}
	
	else {
		printf("%s was not coppied to %s\n", TEXT, TEXTO);
	}

	fclose(in);
	fclose(out);
	free(k);
}

