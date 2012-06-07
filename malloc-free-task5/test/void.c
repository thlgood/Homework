#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *test = malloc(8);
	int *p = (int *)test;
	*p = 14;
//	*(test + 4) = NULL;
//	*(test + 8) = NULL;
	free(test);
	return 0;
}
