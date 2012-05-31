#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef BUFSIZ
#undef BUFSIZ
#define BUFSIZ 10000

int main(int argc, char *argv[])
{
	FILE 	*fp = NULL;
	char	*buf = (char *)malloc(sizeof(char)*BUFSIZ);

	size_t	bufused = 0;
	size_t  buflen = BUFSIZ;
	size_t  last_read = 0;

	if(argc != 2)
	{
		fputs("Too less argument!\n", stderr);
		return 1;
	}

	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		perror("fopen");
		return 1;
	}

	while ((last_read = fread(buf, sizeof(char), BUFSIZ, fp)) == BUFSIZ)
	{
		bufused += BUFSIZ;
		if((buflen - bufused) < BUFSIZ)
		{
			buf = realloc(buf, buflen + BUFSIZ);
			buflen += BUFSIZ;
		}
	}
	bufused += last_read;

	fclose(fp);
	if ((fp = fopen(argv[1], "w")) == NULL)
	{
		perror("fopen");
		return 1;
	}
	while (bufused != 0)
		fwrite(&buf[--bufused], sizeof(char), 1, fp);

	fclose(fp);
	free(buf);
	return 0;
}
#endif
