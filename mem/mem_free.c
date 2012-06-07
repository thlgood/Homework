#include "common.h"
#include <stdbool.h>
#include <assert.h>
#define UP   1
#define DOWN 2

typedef int  JUMP_TYPE;

static void *jump_to(void *p, JUMP_TYPE up_down)
{
    Bt4 size;
    if (UP == up_down) {
        size = abs(*(Bt4 *)(p - 4));
        return p + size;
    }
    else {
        size = abs(*(Bt4 *)(p + 4));
        return p - size;
    }
}

void *mem_free(void *p)
{
    Bt4 *block_head = p - 4;
    Bt4 *block_tail;
    if (*block_head < 0)
    {
        return (void *)-1;
    }

    block_tail = (Bt4 *)(p + (*block_head) - 4);

    //find empty block
    Bt4 *empty_finder_down = block_tail;
    Bt4 *empty_finder_up = block_head;

    while (empty_finder_up > pool_head && *empty_finder_up > 0)
    {
        empty_finder_up = jump_to((void *)empty_finder_up, UP);
    }
    if (*empty_finder_up > 0)
    {
        void *temp = empty_finder_up;
        empty_finder_up = (Bt*4)(temp + *(empty_finder_up));
    }

    while (empty_finder_down < pool_tail && *empty_finder_down > 0)
    {
        empty_finder_down = jump_to((void *)empty_finder_down, DOWN);
    }
    if (*empty_finder_down > 0)
    {
        void *temp = empty_finder_down;
        empty_finder_down = (Bt*4)(temp - *(empty_finder_down));
    }
    //---上面的 emtpy_finder_down和empty_finder_up是合并后的首尾

    if (pool_empty == (void *)empty_finder_up || pool_head == (void*)empty_finder_up)
    {
        *(empty_finder_up + 2) = 0;
    }
    else
    {
        void *p;
        p = jump_to((void *)empty_finder_up, UP);
        p = jump_to(p, UP);
        *(empty_finder_up + 2) = (Bt4)p;
        *(p + 4) = empty_finder_up;
    }

    if (pool_tail == (void *)empty_finder_down ||
        pool_tail == jump_to((void *)empty_finder_down, DOWN))
    {
        *(empty_finder_up + 2) = 0;
    }
    else
    {
        void *p  = jump_to((void *)empty_finder_up, DOWN) + 4;
        *(empty_finder_up + 1) = (Bt4)p;
        *(p - 4) = empty_finder_up;
    }
}


