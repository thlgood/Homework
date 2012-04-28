#include "head.h"
#include <iostream>
#include <pthread.h>

//int search(const char *file_path, const char *id);

void autosearch()
{
    int line = 0;
    while (1)
    {
        pthread_mutex_lock(&path_mutex);
        if(all_paths.size())
        {
            line = search(all_paths.back().c_str, id);
            if (line > 0)
                printf("%d: %s\n", line, all_paths.back().c_str);
            all_paths.pop_back();
        }
        else
        {
            pthread_mutex_unlock(&path_mutex);
            //pthread_exit(NULL);
            break;
        }
        pthread_mutex_unlock(&path_mutex);
    }
    pthread_exit(NULL);
}
