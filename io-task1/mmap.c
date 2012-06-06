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
	off_t	size, count;//file size
	char *char_buf;
	struct stat file_stat;

	if (argc < 2)
	{
		fputs("Too less argument!\n", stderr);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);
	fstat(fd, &file_stat);
	size = file_stat.st_size;
	char_buf = mmap(0, size, PROT_READ, MAP_PRIVATE|MAP_NORESERVE, fd, 0);

	if (char_buf == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	freopen("temp_file", "w", stdout);
	
	char_buf += size -1;
	for (; size != 0; size--, char_buf--)
		putchar(*char_buf);

	close(fd);
	fflush(stdin);
	remove(argv[1]);
	rename("temp_file", argv[1]);
	return 0;
}
