#include "head.h"
#include <pthread.h>
#include 
extern int thread_count;
extern char *path;

int main(int argc, char *argv[])
{
    //Check args
    checkArgs(&argc, &argv);



    //Create threads
    thread_t *thread_all = malloc(sizeof(pthread_t) * thread_count);
    int t_count = thread_count;

    for (t_count = 0; t_count < thread_count, t_count++)
        pthread_create(&thread_all[t_count], NULL, search, (void*)one[count]);

    for (t_count = 0; t_count < thread_count, t_count++)
        pthread_join(thread_all[t_count], NULL);

    free(thread_all);
    return 0;
}
