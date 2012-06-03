#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>		// for fstat
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int fd;				//file descriptor
	size_t	size, count;//file size
	char *char_buf;
	struct stat file_stat;
	char buf[10000];

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}

	if (fstat(fd, &file_stat) < 0)
	{
		perror("fstat");
		exit(EXIT_FAILURE);
	}

	size = file_stat.st_size;
	char_buf = mmap(0, size, PROT_READ, MAP_PRIVATE|MAP_NORESERVE, fd, 0);
	if (char_buf == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	buf[size] = '\0';
	for (; size != 0; size--, char_buf++)
		buf[size-1] = *char_buf;
	freopen(argv[1], "w", stdout);
	printf("%s", buf);
	close(fd);
	return 0;
}
