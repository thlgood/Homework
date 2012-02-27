#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>	//S_IRUSR etc in open() function!

int main(int argc, char *argv[])
{
	int 	fd;
	int		tmp_fd;
	size_t 	bufused = 0;
	size_t  bufsize = BUFSIZ;
	size_t  read_last = 0;
	char 	*buf = malloc(sizeof(char)*BUFSIZ);
	char	*tmpfile; 

	if(argc != 2)
	{
		fputs("Too less argument!\n", stderr);
		return 1;
	}
	
	tmpfile = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	strcpy(tmpfile, argv[1]);
	strcat(tmpfile, "~");

	if((fd = open(argv[1], O_RDONLY)) == 0)
	{
		perror("open");
		return 1;
	}

	if((tmp_fd = open(	tmpfile, 
						O_WRONLY|O_CREAT, 
  						S_IRUSR|S_IWUSR|S_IROTH)) == 0)
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
	
	size_t bufprint = bufused;
	while (bufprint != 0)
	{
		write(tmp_fd, &buf[--bufprint], 1);
	}
		//putchar(buf[--bufprint]);
	close(fd);
	close(tmp_fd);
	free(buf);
	remove(argv[1]);
	rename(tmpfile, argv[1]);
	free(tmpfile);

	return 0;
}
