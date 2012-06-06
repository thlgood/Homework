/*
 *任务: 进程/线程同步
 *作者: 唐恒亮
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

#define SEM_COUNT    5
#define TIME         8 

void print(int id, int count);
void allocate_signal(int id);
void free_signal(int id);
void fork_process(int n);

int flag = -1;
int Sem  = -1;

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int main()
{
	int   i;
	pid_t ppid = getpid();
	print (1, TIME);
	
	Sem = semget(IPC_PRIVATE, SEM_COUNT, 0666|IPC_CREAT|IPC_EXCL);

	fork_process(5);
	if (getpid() == ppid)
	{
		for (i = 0; i < 5; i++)
		{
			int status;
			wait(&status);
		}
	}

	switch(flag)
	{
		case 2:
			print (2, TIME);
			free_signal(0);
			free_signal(1);
			break;
		case 3:
			print (3, TIME);
			free_signal(2);
			break;
		case 4:
			allocate_signal(0);
			print (4, TIME);
			free_signal(3);
			break;
		case 5:
			allocate_signal(1);
			allocate_signal(2);
			print (5, TIME);
			free_signal(4);
			break;
		case 6:
			allocate_signal(3);
			allocate_signal(4);
			print (6, TIME);
			break;
		default:
			fprintf(stderr, "UNKNOW process:%d\n", flag);
			break;
	}
	return 0;
}

void allocate_signal(int id)
{
	struct sembuf spos = {id, -1, 0};

	if (semop(Sem, &spos, 1))
	{
		perror("Allocate");
		printf("ID:%d\n", id);
	}
}

void free_signal(int id)
{
	struct sembuf spos = {id, 1, IPC_NOWAIT};

	if (semop(Sem, &spos, 1))
	{
		perror("Free");
		printf("ID:%d\n", id);
	}
}


void print(int id, int count)
{
	while (count--)
	{
		printf("I am Process %d\n", id);
	}
}

void fork_process(int n)
{
	pid_t pid;

	for (flag = 0; flag < n; flag++ )
	{
		pid = fork();
		if (pid == 0)
		{
			flag = flag + 2;
			break;
		}
	}
}
