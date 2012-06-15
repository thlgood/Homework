#include "common.h"


//块的起始位置
void *pool_head = NULL;
//块末尾的位置
void *pool_tail = NULL;

void *mem_allocate(int size)
{
	//确定要分配的大小，保证size%8 == 0
	size = (size % 8 == 0) ? size: ((size/8) + 1) * 8;


	if (NULL == pool_head)
	{
		pool_head = sbrk(BUF_LENGTH);
		if (pool_head == (void *)-1)
		{
			errno = ENOMEM;
			return pool_head;
		}
		pool_tail = sbrk(0);
		TO_INT(pool_head)     = BUF_LENGTH * -1;
		TO_INT((pool_tail - 4)) = BUF_LENGTH * -1;
	}

	void *finder = pool_head;
	while (finder < pool_tail &&        //末尾之前
	       (TO_INT(finder) > 0 ||       //足够大
	       TO_ABS_INT(finder) < size)
		  )
	{
		finder = jump_to_next(finder);
	}
	if (finder > pool_tail)
	{
		errno = ENOMEM;
		return (void *) -1;
	}
	
	if ((TO_ABS_INT(finder)) - size <= 8)
	{
		void *tail     = jump_to_tail(finder);
		TO_INT(finder) = TO_ABS_INT(finder);
		TO_INT(tail)   = TO_ABS_INT(tail);
		return finder + 4;
	}
	else if ((TO_ABS_INT(finder)) - size > 8)
	{
		void *eb_head;
		void *eb_tail;
		int  bl_size = TO_ABS_INT(finder);
		int  fb_size = size + 8;
		int  eb_size = bl_size - fb_size;
		
		eb_tail = jump_to_tail(finder);
		eb_head = finder + size + 8;
		TO_INT(finder) = fb_size;
		TO_INT((eb_head - 4)) = fb_size;
		
		TO_INT(eb_head) = eb_size * -1;
		TO_INT(eb_tail) = eb_size * -1;
		
		return finder + 4;
		
	}
}
