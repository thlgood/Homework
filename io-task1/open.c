#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BLOCK_SIZE 256

void revCopy(char *strOne, char *strTwo, size_t size);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fputs("Too lss argument!", stderr);
		exit(EXIT_FAILURE);
	}
	
	int fdOne = open(argv[1], O_RDONLY);
	int fdTwo = creat("temp_file", 00644);
	char buf_one[BLOCK_SIZE];
	char buf_two[BLOCK_SIZE];
	size_t count;
	
	while ((count = read(fdOne, buf_one, BLOCK_SIZE)) && count != -1)
	{
		revCopy(buf_one, buf_two, count);
		write(fdTwo, buf_two, count);
		if (count != BLOCK_SIZE) 
			break;
	}

	close(fdOne);
	close(fdTwo);
	remove(argv[1]);
	if(rename("temp_file", argv[1]) != 0)
	{
		perror("rename");
		exit(EXIT_FAILURE);
	}

	return 0;
}
void revCopy(char *strOne, char *strTwo, size_t size)
{
	size_t temp;
	for (temp = 0; temp < size; temp++)
	{
		strTwo[temp] = strOne[size-temp-1];
	}
}
