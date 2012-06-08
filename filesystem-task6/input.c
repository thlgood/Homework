#include "common.h"

#define PS "EFB $"

int input(char *input_buffer)
{
	char arg[2];
	char buf[1024];

	strcpy(argv[0], "NOT");
	strcpy(argv[1], "NOT");
	fgets(buf, 1024, stdin);
	
	sscanf(buf, "%s%s", arg[0], arg[1]);

	if (strcmp(arg[0], "NOT") != 0)
	{
		strcat(input_buffer, arg[1]);
	}
	else
	{
		return 0;
	}

	if (strcmp(arg[1], "NOT") != 0)
	{
		strcat(input_buffer, " ");
		strcat(input_buffer, arg[1]);
	}

	return strlen(input_buffer);
}
