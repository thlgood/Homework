#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#define TIME 8
int Sem = -1;

static void allocate_signal(int id)
{
	struct sembuf spos = {id, -1, 0};

	if (semop(Sem, &spos, 1) < 0)
	{
		perror("Allocate");
		printf("ID:%d\n", id);
	}
}

static void free_signal(int id)
{
	struct sembuf spos = {id, 1, 0};

	if (semop(Sem, &spos, 1) < 0)
	{
		perror("Free");
		printf("ID:%d\n", id);
	}
}


static void print(int id, int count)
{
	while (count--)
	{
		printf("I am Process %d\n", id);
		sleep(1);
	}
}

int main()
{
    Sem = semget(IPC_PRIVATE, 7, 0666|IPC_CREAT|IPC_EXCL);
    if (fork() == 0) //P2
    {
        allocate_signal(0);
        print(2, TIME);
        free_signal(2);
        free_signal(3);
    }
    else
    {
        if (0 == fork()) //P3
        {
            allocate_signal(1);
            print(3, TIME);
            free_signal(4);
        }
        else
        {
            if (0 == fork()) // P4
            {
                allocate_signal(2);
                print(4, TIME);
                free_signal(5);
            }
            else
            {
                if (0 == fork()) // P5
                {
                    allocate_signal(3);
                    allocate_signal(4);
                    print(5, TIME);
                    free_signal(6);
                }
                else
                {
                    if (0 == fork()) // P6
                    {
                        allocate_signal(5);
                        allocate_signal(6);
                        print(6, TIME);
                    }
                    else // P1
                    {
                        print(1, TIME);
                        free_signal(0);
                        free_signal(1);
                        wait(NULL);
                        wait(NULL);
                        wait(NULL);
                        wait(NULL);
                        wait(NULL);
                    }
                }
            }
        }

    }
    return 0;
}

