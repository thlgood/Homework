#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#define SEM_COUNT	1
int Sem  = -1;
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

void print(int id, int count)
{
	while (count--)
	{
		printf("I am Process %d\n", id);
	//	sleep(1);
	}
}

void seminit()
{
	int i;
//	struct sembuf spos[1];
	struct sembuf spos;
	spos.sem_num = 0;
	spos.sem_op  = 1;
	spos.sem_flg = SEM_UNDO;

//	union semun arg;
//	unsigned short group[1] = {0};

//	arg.array = group;
	Sem = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT|IPC_EXCL);
	if(semop(Sem, &spos, 1) == -1)
	{
		perror("----44---");
	}
	printf("Sem = %d\n", Sem);
}

void try_opt(int id)
{
	struct sembuf spos;
	spos.sem_num = id;
	spos.sem_op  = -1;
	spos.sem_flg = SEM_UNDO;

	int retV = semop(Sem, &spos, 1);
	if (retV == -1)
	{
		perror("semop in try");
		printf("ID:%d\n", id);
	}
}

void finish_opt(int id)
{
	struct sembuf spos;
	spos.sem_num = id;
	spos.sem_op  = 1;
	spos.sem_flg = SEM_UNDO;

	int retV = semop(id, &spos, 1);
	if (retV == -1)
	{
		perror("semop in finish_opt");
		printf("ID:%d\n", id);
	}
}


int main (int argc, char *argv[]) 
{
	seminit();
	pid_t pid = fork();
	
	if (!pid)
	{
		try_opt(0);
	}
	else
	{
		print(1, 1);
		finish_opt(0);
	}

	int status;
	wait(&status);
	return 0;
}

