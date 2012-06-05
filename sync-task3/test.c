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


void seminit()
{
	int i;
	struct sembuf spos;
	spos.sem_num = 0;
	spos.sem_op  = 1;
	spos.sem_flg = SEM_UNDO;

	Sem = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT|IPC_EXCL);
	if(semop(Sem, &spos, 1) == -1)
	{
		perror("----44---");
	}
	printf("Sem = %d\n", Sem);
}

int main (int argc, char *argv[]) 
{
	seminit();
	pid_t pid = fork();
	
	if (!pid)
	{
		struct sembuf spos = {0, -1, SEM_UNDO};
		if (semop(Sem, &spos, 1) == -1)
		{
			perror("semop in son");
			exit(1);
		}
		printf("SON Process\n");
	}
	else
	{
		printf("FATHER Process\n");
		struct sembuf spos = {0, -1, SEM_UNDO};

		if (semop(Sem, &spos, 1) == -1)
		{
			perror("semop in father");
			exit(1);
		}
		int status;
		wait(&status);
	}
	return 0;
}

