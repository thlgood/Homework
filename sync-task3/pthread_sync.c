#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LOCK(a)     pthread_mutex_lock(a)
#define UNLOCK(a)   pthread_mutex_unlock(a)
#define TRY_LOCK(a) pthread_mutex_trylock(a)
#define TIME       4 
typedef pthread_mutex_t Pmt;

void *func(void *arg);
void print(int id, int count);
void *showID(void *argv);
Pmt mutex[5];

int main()
{
	int i;
	int arg[5];
	pthread_t id[5];

	for (i = 0; i < 5; i++)
		pthread_mutex_init(&mutex[i], NULL);

	//P1
	print(1, TIME);

	for (i = 0; i < 5; i++)
	{
		arg[i] = i;
		pthread_create(&id[i], NULL, func, (void *)&arg[i]);
//		pthread_create(&id[i], NULL, showID, (void *)&arg[i]);
	}

//	for (i = 0; i < 5; i++)
//		pthread_join(id[i], NULL);
	sleep(5);

	return 0;
}

void print(int id, int count)
{
	while (count--)
		printf("I am thread %d\n", id);
}

void *func(void *arg)
{
	//i = 0代表P2,所以id = arg+2
	int id = *(int *)arg;
	id += 2;

	switch(id)
	{
		case 2:
			print(2, TIME);
			LOCK(&mutex[0]);
			LOCK(&mutex[1]);
			break;
		case 3:
			print(3, TIME);
			LOCK(&mutex[2]);
			break;
		case 4:
			while (TRY_LOCK(&mutex[0]) == 0)
			{
				UNLOCK(&mutex[0]);
			}
			print(4, TIME);
			LOCK(&mutex[3]);
			break;
		case 5:
			while ((TRY_LOCK(&mutex[1]) == 0) || 
			       (TRY_LOCK(&mutex[2]) == 0))
			{
				UNLOCK(&mutex[1]);
				UNLOCK(&mutex[2]);
			}
			print (5, TIME);
			LOCK(&mutex[4]);
			break;
		case 6:
			while ((TRY_LOCK(&mutex[3]) == 0) ||
				   (TRY_LOCK(&mutex[4]) == 0))
			{
				UNLOCK(&mutex[3]);
				UNLOCK(&mutex[4]);
			}
			print(6, TIME);
			break;
		default:
			fprintf(stderr, "UNKNOW ID :%d\n", id);
			break;
	}
	pthread_exit(NULL);
}

void *showID(void *argv)
{
	printf("ID=%d\n", *(int *)argv);
	pthread_exit(NULL);
}
