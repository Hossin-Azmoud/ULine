#include <stdio.h>
#include <stdlib.h>




int main(void)
{	
	size_t a = 10;
	void *ptr = malloc(a);

	for(; a > 0; a--)
	{
		(ptr + a - 1) = 0;
	}

	return 0; 
}






