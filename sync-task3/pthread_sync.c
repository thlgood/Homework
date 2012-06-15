/*
 *任务三:进程/线程同步
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define LOCK(a)     pthread_mutex_lock(a)
#define UNLOCK(a)   pthread_mutex_unlock(a)
#define TRY_LOCK(a) pthread_mutex_trylock(a)
#define TIME        30 
#define DEBUG

typedef pthread_mutex_t Pmt;
void *func(void *arg);
void print(int id, int count);
Pmt mutex[5];

int main()
{
	int       i;
	int       arg[5];
	int       retv;
	pthread_t id[5];

	//创建5个互斥锁并将锁住
	for (i = 0; i < 5; i++)
	{
		pthread_mutex_init(&mutex[i], NULL);
		retv = LOCK(&mutex[i]);
		assert(retv == 0);
	}

	//P1完成输出工作
	print(1, TIME);

	//创建五个线程
	for (i = 0; i < 5; i++)
	{
		arg[i] = i;
		pthread_create(&id[i], NULL, func, (void *)&arg[i]);
	}

	//等待线程的退出
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

	int retv_a;
	int retv_b;
	switch(id)
	{
		case 2:
			print(2, TIME);
			retv_a = UNLOCK(&mutex[0]);
			retv_b = UNLOCK(&mutex[1]);
			assert(retv_a == 0);
			assert(retv_b == 0);
			break;
		case 3:
			print(3, TIME);
			retv_a = UNLOCK(&mutex[2]);
			assert(retv_a == 0);
			break;
		case 4:
			LOCK(&mutex[0]);
			print(4, TIME);
			UNLOCK(&mutex[3]);
			break;
		case 5:
			LOCK(&mutex[1]);
			LOCK(&mutex[2]);
			print (5, TIME);
			UNLOCK(&mutex[4]);
			break;
		case 6:
			LOCK(&mutex[3]);
			LOCK(&mutex[4]);
			print(6, TIME);
			break;
		default:
			fprintf(stderr, "UNKNOW ID :%d\n", id);
			break;
	}
	pthread_exit(NULL);
}
