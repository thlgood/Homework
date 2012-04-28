#include "head.h"
#include <pthread.h>
#include <vector>
#include <string>
//extern int thread_count;

int main(int argc, char *argv[])
{
    //Check args
    checkArgs(&argc, &argv);

    //Create threads
    pthread_t thread_all[pthread_count];
    int t_count;

    for (t_count = 0; t_count < pthread_count; t_count++)
        pthread_create(&thread_all[t_count], NULL, autosearch, NULL);

    for (t_count = 0; t_count < pthread_count; t_count++)
        pthread_join(thread_all[t_count], NULL);

    return 0;
}
