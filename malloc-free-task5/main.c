#include "common.h"
#include <string.h>

int main()
{
	char *name = (char *)mem_allocate(10);
	strcpy(name, "唐恒亮");
	printf("My name is %s\n", name);
	mem_free(name);
	name = (char *)mem_allocate(10);
	return 0;
}
