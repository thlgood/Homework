#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *p = "\t\nhello, yahoo sina";
	char *name = malloc(8);
	char *num = malloc(8);
	strcpy(num, "NOT");
	sscanf(p, "%s%s", NULL, num);
//	printf("%s\n", name);
	printf("%s\n", num);
	return 0;
}
