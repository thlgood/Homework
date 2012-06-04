#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LOCK(a)     pthread_mutex_lock(a)
#define UNLOCK(a)   pthread_mutex_unlock(a)
#define TRY_LOCK(a) pthread_mutex_trylock(a)
#define TIME        14 

#define DEBUG

typedef pthread_mutex_t Pmt;
void *func(void *arg);
void print(int id, int count);
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
	}

	for (i = 0; i < 5; i++)
	{
		pthread_join(id[i], NULL);
	}
	return 0;
}

void print(int id, int count)
{
	while (count--)
	{
		printf("I am thread %d\n", id);
	}
}

void *func(void *arg)
{
	//i = 0代表P2,所以id = arg+2
	int id = *(int *)arg;
	id += 2;

	int mutex_a;
	int mutex_b;
	switch(id)
	{
		case 2:
			print(2, TIME);
			while (LOCK(&mutex[0]) != 0) NULL;
			while (LOCK(&mutex[1]) != 0) NULL;
			break;
		case 3:
			print(3, TIME);
			while (LOCK(&mutex[2]) != 0) NULL;
			break;
		case 4:
			while ((mutex_a = TRY_LOCK(&mutex[0])) == 0)
			{
#ifdef 		DEBUG
				printf("4 mutex_a=%d\n", mutex_a);
#endif
				UNLOCK(&mutex[0]);
				sleep(1);
			}
			print(4, TIME);
			while (LOCK(&mutex[3]) != 0) NULL;
			break;
		case 5:
			while (((mutex_a = TRY_LOCK(&mutex[1])) == 0) || 
			       ((mutex_b = TRY_LOCK(&mutex[2])) == 0))
			{
#ifdef 		DEBUG
				printf("5 mutex_a=%d mutex_b=%d\n", mutex_a, mutex_b);
#endif
				UNLOCK(&mutex[1]);
				UNLOCK(&mutex[2]);
				sleep(1);
			}
			print (5, TIME);
			while (LOCK(&mutex[4]) != 0) NULL;
			break;
		case 6:
			while (((mutex_a = TRY_LOCK(&mutex[3])) == 0) ||
				   ((mutex_b = TRY_LOCK(&mutex[4])) == 0))
			{
#ifdef 		DEBUG
				printf("6 mutex_a=%d mutex_b=%d\n", mutex_a, mutex_b);
#endif
				UNLOCK(&mutex[3]);
				UNLOCK(&mutex[4]);
				sleep(1);
			}
			print(6, TIME);
			break;
		default:
			fprintf(stderr, "UNKNOW ID :%d\n", id);
			break;
	}
	pthread_exit(NULL);
}
