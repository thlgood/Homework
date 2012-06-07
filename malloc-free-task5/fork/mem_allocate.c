#include "common.h"

void *pool_head = NULL;
void *pool_tail = NULL;

void *mem_allocate(int size)
{
	if (NULL == pool_head)
	{
		pool_head = sbrk(BUF_LENGTH);
		if (pool_head == (void *)-1)
			return pool_head;
		pool_tail = sbrk(0);
		TO_INT(pool_head)     = BUF_LENGTH * -1;
		TO_INT(pool_tail - 3) = BUF_LENGTH * -1;
	}

	void *finder = pool_head;
	while (finder < pool_tail && TO_INT(finder) > 0)
	{

	}
}
