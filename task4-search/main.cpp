#include "head.h"
#include <pthread.h>
#include <vector>
#include <string>


int main(int argc, char *argv[])
{
    //Check args
    checkArgs(&argc, &argv);

    //Create threads
    thread_t thread_all[thread_count];
    int t_count;

    for (t_count = 0; t_count < thread_count, t_count++)
        pthread_create(&thread_all[t_count], NULL, autosearch, (void*)one[count]);

    for (t_count = 0; t_count < thread_count, t_count++)
        pthread_join(thread_all[t_count], NULL);

    return 0;
}
