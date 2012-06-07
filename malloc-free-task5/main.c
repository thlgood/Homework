#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_LENGTH    1024*64  //64K buffer

void Malloc(size_t size);
void Free(void *p);

void *bufInit();
void *bufHead = NULL;
void *bufTail = NULL;

int main(void)
{
	char *name = NULL;
	name = (void *)Malloc(13);
	strcpy(name, "唐恒亮");
	printf ("%s\n", name);
	Free(&name);
	return 0;
}

void *bufInit()
{
	if ((bufHead = sbrk(BUF_LENGTH)) == (void *)-1)
	{
		bufHead = NULL;
		bufTail = NULL;
		return NULL;
	}

	int32_t *BIT4 = *bufHead;
	*BIT4 = BUF_LENGTH;
	*(BIT4+1) = 0x0;  //NULL
	*(BIT4+2) = 0x0;  //NULL
	bufTail = sbrk(0);

	return bufHead;
}

void *Malloc(size_t size)
{
	if (bufHead == NULL)
	{
		if (bufInit() == NULL)
			return NULL;
	}

	int32_t *fourBitP = bufHead;      //4字节指针
	int32_t remainder = (size / 8);   //余数
	int32_t totalSize;                //用户存储+记录空间
	totalSize = (remainder == 0)? (size + 8) : (size%8 + 2)*8;

	if (BUF_LENGTH < totalSize)
		return NULL;
	
	uint32_t *flag = fourBitP = (uint32_t *)bufHead;
	while (*flag != bufTail)
	{
		if (*fourBitP - totalSize > 3*4)
		{
			uint32_t next_block = *(fourBitP+1);
			uint32_t last_block = *(fourBitP+2);
			uint32_t new_block = 0;
			uint32_t *temp;
			*fourBitP = totalSize;
			new_block = fourBitP + (totalSize/4);

			if (next_block != NULL)
			{

				temp = (uint32_t *)next_block; 
				*(temp + 2) = (uint32_t)last_block;
			}
			else
			{
				temp = (uint32_t*)next_block;
				*(temp + 2) = new_block;
				temp = (uint32_t *)new_block;
				*(temp+1) = NULL;
				*(temp+2) = (uint32_t)last_block;
			}
			if (last_block != NULL)
			{
				temp = (uint32_t *)last_block;
				*(temp + 1) = (uint32_t)next_block;
			}
			return (void*)(fourBitP+2);
		}
		else if ()
	}
}
void Free(void *p)
{

	*p = NULL;
}
