#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>

int Sem = -1;

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
//int Sem  = -1;

void seminit()
{
	Sem = semget(IPC_PRIVATE, 2, 0666|IPC_CREAT|IPC_EXCL);
	printf("Sem = %d\n", Sem);
}

int main (int argc, char *argv[]) 
{
	seminit();
	pid_t pid = fork();
	
	if (!pid)
	{
		/*struct sembuf spos_1 = {0, -1, SEM_UNDO};
		struct sembuf spos_2 = {1, -1, SEM_UNDO};
		if (semop(Sem, &spos_1, 1) == -1)
		{
			perror("semop in son 1");
			exit(1);
		}
		if (semop(Sem, &spos_2, 1) == -1)
		{
			perror("semop in son 1");
			exit(1);
		}*/
		allocate_signal(0);
		allocate_signal(1);
		printf("SON 1 Process\n");
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			printf("SON 2 Process\n");
			/*struct sembuf spos = {0, 1, 0};
			if (semop(Sem, &spos, 1) == -1)
			{
				perror("semop in son 1");
				exit(1);
			}*/
			free_signal(0);
		}
		else
		{
			sleep(1);
			printf("FATHER Process\n");
			/*struct sembuf spos = {1, 1, 0};
			if (semop(Sem, &spos, 1) == -1)
			{
				perror("semop in father");
				exit(1);
			}*/
			free_signal(1);
			int status;
			wait(&status);
			wait(&status);
		}
	}
	return 0;
}
