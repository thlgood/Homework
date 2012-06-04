#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *func(void *arg)
{
	printf("ID=%d\n", *(int*)arg);
	pthread_exit(NULL);
}

int main()
{
	pthread_t pt[4];
	int arg[4];
	int i;

	for (i =0 ; i < 4; i++)
	{
		arg[i] = i;
		pthread_create(&pt[i], NULL, func, (void*)&arg[i]);
	}
	sleep(1);
	return 0;
}
