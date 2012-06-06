#include "Tshell.h"

void init_arg(int argc, char *argv[])
{
	switch(argc)
    	{
		case 1:
			break;
		case 2:
			if (!strcmp("-v", argv[1]))
			{
				run_mode = IS_DEBUG_MODE;
			}
			else
			{
				freopen(argv[1], "r", stdin);
			}
			break;
		case 3:
			run_mode = IS_DEBUG_MODE;
			if (strcmp("-v", argv[1]))
			{
				freopen(argv[1], "r", stdin);
			}
			else
			{
				freopen(argv[2], "r", stdin);
			}
			break;
		default:
			fputs("Too much argument!", stderr);
			exit(EXIT_FAILURE);
	}
}

bool input(char *line)
{
	int count = 0;
	line[BUF_LEN - 1] = '\0';
	char buf;

	fputs("> ", stdout);

	while (count < (BUF_LEN) && (buf = getchar()))
	{
		if (0 == count)
		{
			if (buf == '\n')
			{
				return false;
			}
			else if (buf == EOF)
			{
				putchar('\n');
				return false;
			}
			else if (buf == ' '|| buf == '\t')
			{
				continue;
			}
			else
			{
				line[0] = buf;
				count++;
			}
		}
		else
		{
			if (buf == '\n' || buf == EOF)
			{
				line[count] = '\0';
				return true;
			}
			line[count] = buf;
			count++;
		}
	}
	line[BUF_LEN-1] = '\0';
	return true;
}

