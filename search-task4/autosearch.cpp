#include "head.h"
#include <limits.h>
#include <iostream>
#include <pthread.h>
#include <string.h>
#include <string>
using namespace std;


void *autosearch(void *arg_no_use)
{
	int line = 0;
	while (1)
	{
		pthread_mutex_lock(&paths_mutex);
		if(all_paths.size())
		{
			line = search(all_paths.back().c_str(), id.c_str());
			if (line > 0)
				printf("%d: %s\n", line, all_paths.back().c_str());
			all_paths.pop_back();
		}
		else
		{
			pthread_mutex_unlock(&paths_mutex);
			break;
		}
		pthread_mutex_unlock(&paths_mutex);
	}
	pthread_exit(NULL);
}
