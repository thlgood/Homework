#ifndef COMMOM_H
#define COMMOM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define BUF_LENGTH 1024*64

#define TO_INT(a)      (*(int *)a)
#define INT_PTR(a)     (int *)a
#define TO_ABS_INT(a)  abs(*(int *)a)

extern void *pool_head;
extern void *pool_tail;

void *mem_allocate(int size);
void *mem_free(void *p);


inline void *jump_to_tail(void *head);
inline void *jump_to_head(void *tail);
inline void *jump_to_last(void *head);
inline void *jump_to_next(void *tail);

#endif
