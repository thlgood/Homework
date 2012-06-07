#ifndef COMMOM_H
#define COMMOM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

//64KB
#define BUFSIZE 1024*64

//4个字节为一个单元 1 Bt4=4 Bytes
typedef int32_t Bt4;

extern pool_head;
extern pool_tail;

void *update_empty_list();
void *mem_allocate(size_t size);
void *mem_free(void *p);

#endif
