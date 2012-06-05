/*
 *任务: 进程/线程同步
 *作者: 唐恒亮
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>

#define SEM_COUNT	5
#define FINISHED    1
#define UNFINISHED  2
#define TIME        10 

void seminit();
void print(int id, int count);
void finish_opt(int id);
void try_opt(int id);

int flag = -1;
int Sem  = -1;

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main()
{
	int   i;
	pid_t child[5];

	seminit();

	for(i = 0; i < 5; i++)
	{
		child[i] = fork();
		if (child[i] == 0)
			flag = i + 2;
	}
	if (flag == -1)
	{
		print (1, TIME);
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
			finish_opt(0);
			finish_opt(1);
			break;
		case 3:
			print (3, TIME);
			finish_opt(2);
			break;
		case 4:
			try_opt(0);
			print (4, TIME);
			finish_opt(3);
			break;
		case 5:
			try_opt(1);
			try_opt(2);
			print (5, TIME);
			finish_opt(4);
			break;
		case 6:
			try_opt(3);
			try_opt(4);
			print (6, TIME);
			break;
		default:
			fprintf(stderr, "UNKNOW process:%d\n", flag);
			break;
	}
	return 0;
}

void seminit()
{
	int i;
	key_t key = ftok("./key", 'E');
	Sem = semget(key, SEM_COUNT, 0666|IPC_CREAT|IPC_EXCL);
	if (Sem < 0)
	{
		if (errno != EEXIST)
		{
			perror("semget");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < SEM_COUNT; i++)
	{
		union semun semval;
		semval.val = 0;
		int retV = semctl(Sem, i, SETVAL, semval);
		assert(retV >= 0);
	}
}

void try_opt(int id)
{
	struct sembuf spos = {id, -1, 0};
	int retV = semop(Sem, &spos, 1);
	assert(retV > 0);
}

void finish_opt(int id)
{
	struct sembuf spos = {id, 1, IPC_NOWAIT};
	int retV = semop(id, &spos, 1);
	assert(retV >= 0);
}


void print(int id, int count)
{
	while (count--)
	{
		printf("I am Process %d\n", id);
	}
}
