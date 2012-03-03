#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>	//S_IRUSR etc in open() function!

int main(int argc, char *argv[])
{
	int 	fd;
	size_t 	bufused = 0;
	size_t  bufsize = BUFSIZ;
	size_t  read_last = 0;
	char 	*buf = malloc(sizeof(char)*BUFSIZ);

	if(argc != 2)
	{
		fputs("Too less argument!\n", stderr);
		return 1;
	}

	if((fd = open(argv[1], O_RDONLY)) == 0)
	{
		perror("open");
		return 1;
	}


	while ((read_last = read(fd, &buf[bufused], BUFSIZ)) == BUFSIZ)
	{
		bufused += BUFSIZ;
		if((bufsize-bufused) < BUFSIZ)
		{
			buf = realloc(buf, bufsize+BUFSIZ);
			bufsize += BUFSIZ;
		}
	}
	bufused += read_last;
	close(fd);
	
	size_t bufprint = bufused;
	if((fd = open(	argv[1], 
					O_WRONLY|O_CREAT, 
  					S_IRUSR|S_IWUSR|S_IROTH)) == 0)
	{
		perror("open");
		return 1;
	}
	while (bufprint != 0)
	{
		write(fd, &buf[--bufprint], 1);
	}

	close(fd);
	free(buf);

	return 0;
}
