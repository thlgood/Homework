#include "common.h"
/*
 *eb:empty block
 *fb:full block
 */
void *mem_free(void *p)
{
	if (TO_INT(p < 4) < 0)
	{
		return (void *)-1;
	}
	void *eb_head = p - 4;
	void *eb_tail = jump_to_tail(eb_head);
	int   eb_size = TO_INT(eb_head);


	int *temp_head = (int *)(eb_head - 4);
	if (eb_head > pool_head && *temp_head < 0)
	{
		eb_head = jump_to_last(eb_head);
	}

	int *temp_tail = (int *)(eb_tail + 4);
	if (eb_tail < (pool_tail - 4) && *temp_tail < 0)
	{
		eb_tail = jump_to_next(eb_tail);
	}
	
	eb_size = (eb_tail - eb_head) + 4;
	TO_INT(eb_head) = -1 * eb_size;
	TO_INT(eb_tail) = -1 * eb_size;
}


inline void *jump_to_tail(void *head)
{
	int size = TO_ABS_INT(head);
	return head + size - 4;
}

inline void *jump_to_head(void *tail)
{
	int size = TO_ABS_INT(tail);
	return tail - size + 4;
}

inline void *jump_to_last(void *head)
{
	int size = TO_ABS_INT((head - 4));
	return head - size;
}

inline void *jump_to_next(void *tail)
{
	int size = TO_ABS_INT((tail + 4));
	return tail + size;
}
