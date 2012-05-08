#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "myshell.h"

#define PS2		"> "
#define OUTPUT(arg)	printf("> %s", arg)
#define INPUT(line)	fgets(line, 1024, stdin)

int main(int argc, char *argv[])
{
	char line[1024];	//行缓冲
	if (argc == 1)
	{
		OUTPUT("");
		INPUT(line);
		OUTPUT(line);
	}
	return 0;
}
