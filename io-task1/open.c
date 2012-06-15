#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//把src的内容逆序复制到dst中
void revCopy(char *dst, char *src, size_t size);

int main(int argc, char *argv[])
{
	//判断参数的个数
	if (argc < 3) {
		fputs("Too lss argument!", stderr);
		exit(EXIT_FAILURE);
	}

	int BLOCK_SIZE = atoi(argv[2]);
	struct stat fileInfo;		//fileInfo保存文件的信息

	//open 返回文件描述符 O_RDONLY：只读
	int fd = open(argv[1], O_RDONLY);

	char buf[BLOCK_SIZE];
	char *stack = NULL;     //栈
	
	size_t stackSize = -1;  //栈大小
	size_t count = -1;
	size_t stackTop = 0;    //栈顶下标

	lstat(argv[1], &fileInfo);
	stackSize = fileInfo.st_size; //获取文件大小
	stack = (char *)malloc(stackSize);
	
	/*
	 *将文件内容全部读取到buf中
	 *BLOCK_SIZE：每次要读取的个数
	 *count：每次成功读取到的个数
	 */
	while ((count = read(fd, buf, BLOCK_SIZE)) && count != -1)
	{
		memcpy(&stack[stackTop], buf, count);
		stackTop += count;

		//count != BLOCK_SIZE 读取结束
		if (count != BLOCK_SIZE) break;
	}
	close(fd);

	//以只写的形式打开文件，文件会被截断（清空）
	fd = open(argv[1], O_WRONLY);

	//当栈内元素小于BLOCK_SIZE时，元素个数为count个
	count = stackTop > BLOCK_SIZE ? BLOCK_SIZE : stackTop;
	while (stackTop > 0)
	{
		//复制并翻转
		revCopy(buf, &stack[stackTop-count], count);
		write(fd, buf, count);

		//栈内剩余数据
		stackTop -= count;
		if (stackTop < count)
			count = stackTop;
	}
	close(fd);
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
