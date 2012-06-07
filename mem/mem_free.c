#include "common.h"
#include <stdbool.h>
#include <assert.h>

void *mem_free(void *p)
{
    Bt4 *block_head = p;
    Bt4 *block_tail;
    if (*mem_bursh < 0)
    {
        return (void *)-1;
    }

    block_tail = block_head + (*block_head - 4);

    //find empty block
    Bt4 *empty_finder_down = block_tail -1;

    while (*empty_finder_down > 0 && empty_finder_down < pool_tail)
    {
        Bt4 temp = *empty_finder_down;
        empty_finder_down += temp/4
    }
    if (empty_finder_down - 1 == pool_tail)
        empty_finder_down = pool_tail;

    Bt4 empty_size = empty_finder_down - empty_finder_up + 4;
    assert(empty_size > 0);

}
