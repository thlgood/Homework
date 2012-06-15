#ifndef TS_PL_H
#define TS_PL_H

#include "Tshell.h"
#include "Process.h"


/*
 *PL：Process List子进程列表
 *
 */
struct PL
{ 
	pid_t pid;      //子进程的PID
	char cmd[32];   //子进程的名字
	char **vect;	//子进程的参数
	struct PL *next;
};
typedef struct PL PL;

// malloc PL
#define MALLOC_PL	(PL *)malloc(sizeof(PL))
extern PL *PL_head;//子进程列表表头
extern PL *PL_tail;//表尾

void show_PL();    //输出子进程列表
bool add_to_PL(Process *child);
bool del_from_PL(pid_t pid);
void free_PL();    //清空子进程列表
#endif
