#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 256

void revCopy(char *strOne, char *strTwo, size_t size);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fputs("Too lss argument!", stderr);
		exit(EXIT_FAILURE);
	}
	FILE *temp_fp = fopen("temp_file", "w");
	FILE *fp_in   = fopen(argv[1], "r");
	char buf_one[BLOCK_SIZE];
	char buf_two[BLOCK_SIZE];
	size_t count;
	while (count = fread(buf_one, 1, BLOCK_SIZE, fp_in))
	{
		revCopy(buf_one, buf_two, count);
		fwrite(buf_two, 1, count, temp_fp);
		if (count != BLOCK_SIZE)
			break;
	}

	fclose(fp_in);
	fclose(temp_fp);
	remove(argv[1]);
	rename("temp_file", argv[1]);

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
