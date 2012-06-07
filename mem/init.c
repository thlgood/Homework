#include "common.h"

void *update_empty_list()
{
    if (NULL == pool_head)
    {
        if ((pool_head = sbrk(BUFSIZE)) == (void *)-1)
        {
            pool_head = NULL;
            pool_tail = NULL;
            return NULL;
        }
        else
        {
            pool_tail = sbrk(0);

            Bt4 *size_value;

            //将头尾设置为-size
            size_value = pool_tail;
            *size_value = -1 *BUFSIZE;
            size_value = pool_head;
            *size_value = -1 * BUFSIZE;

            *(size_value + 1) = 0; // NULL
            *(size_value + 1) = 0; // NULL
        }
    }
}
