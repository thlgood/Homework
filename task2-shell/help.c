#include "myshell.h"

bool help()
{
	int errno_temp = errno;	//backup errno
	bool return_val = false;

	FILE *help_file = fopen("help_msg", "r");
	if (help_file == NULL)
	{
		fputs("Could not found help doc!\n", stderr);
		errno = errno_temp;
		return return_val;
	}

	else
	{
		char BUF;
		while ((BUF = fgetc(help_file)) && BUF != EOF)
			putchar(BUF);

		fclose(help_file);
		return true;
	}
}
