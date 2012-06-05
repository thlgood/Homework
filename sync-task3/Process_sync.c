/*
 *任务: 进程/线程同步
 *作者: 唐恒亮
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <assert.h>

int main()
{
	pid_t pid;
	int sem = semget(IPC_PRIVATE, 1, IPC_CREAT);
	assert(sem > 0);

	pid = fork();
	assert(pid !< 0);

}
