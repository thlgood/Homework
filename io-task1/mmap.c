#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>		// for fstat
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int    fd;           //file descriptor
	off_t  size;         //file size
	char   *char_buf;
	struct stat file_stat;

	if (argc < 2) {
		fputs("Too less argument!\n", stderr);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDWR);
	fstat(fd, &file_stat);
	size = file_stat.st_size;

	//映射
	char_buf = mmap(0, 
	                size, 
	                PROT_READ|PROT_WRITE, 	//Read & Write
	                MAP_SHARED,
					fd, 0);

	if (char_buf == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	//开始交换
	int head = 0; 
	int tail = (size - 1);
	char temp;
	for (; head < tail; head++, tail--)
	{
		temp = char_buf[head];
		char_buf[head] = char_buf[tail];
		char_buf[tail] = temp;
	}

	//取消映射
	if (munmap(char_buf, size) == -1)
		perror("Error un-mmapping the file");
	close(fd);
	return 0;
}
