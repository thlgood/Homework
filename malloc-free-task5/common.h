#ifndef COMMOM_H
#define COMMOM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

//4个字节为一个单元
typedef uint32_t Unit4;

extern pool_head;
extern pool_tail;

void *update_empty_list();

#endif
