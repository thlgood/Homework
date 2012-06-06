#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define BLOCK_SIZE 256

void revCopy(char *dst, char *src, size_t size);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fputs("Too lss argument!", stderr);
		exit(EXIT_FAILURE);
	}
	struct stat fileInfo;
	FILE *fp = fopen(argv[1], "r");

	char buf[BLOCK_SIZE];
	char *stack = NULL;

	size_t stackSize = -1;
	size_t count = -1;
	size_t stackTop = 0;

	lstat(argv[1], &fileInfo);
	stackSize = fileInfo.st_size;
	stack = (char *)malloc(stackSize);

	while (count = fread(buf, 1, BLOCK_SIZE, fp))
	{
		memcpy(&stack[stackTop], buf, count);
		stackTop += count;
		if (count != BLOCK_SIZE) break;
	}
	fclose(fp);
	fp = fopen(argv[1], "w");

	count = stackTop > BLOCK_SIZE ? BLOCK_SIZE : stackTop;
	while (stackTop > 0)
	{

		revCopy(buf, &stack[stackTop-count], count);
		fwrite(buf, 1, count, fp);
		stackTop -= count;
		if (stackTop < count)
			count = stackTop;
	}
	fclose(fp);
	return 0;
}
void revCopy(char *dst, char *src, size_t size)
{
	size_t temp;
	for (temp = 0; temp < size; temp++)
	{
		dst[temp] = src[size-temp-1];
	}
}
