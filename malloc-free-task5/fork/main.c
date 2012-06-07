#include "common.h"

int main()
{
	char *name = mem_allocate(10);
	strcpy(name, "唐恒亮");
	printf("My name is %s\n", name);
	mem_free(name);
	return 0;
}
