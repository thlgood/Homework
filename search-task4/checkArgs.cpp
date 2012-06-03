#include "head.h"
#include <string>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

void checkArgs(int *argc, char ***argv)
{
    int searched = 0;
    paths_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_count = 1;
    if (*argc < 3)
    {
        fputs("Too argument!\n", stderr);
        exit(1);
    }
    if (!strcmp((*argv)[1],  "-j"))
    {
        pthread_count = (int)((*argv)[2][0]- '0');
        id = (*argv)[3];

        char *p = (char *)malloc(PATH_MAX);
        realpath((*argv)[4], p);
        catDIR(p);
    }
    else
    {
        id = (*argv)[1];

        char *p = (char *)malloc(PATH_MAX);
        realpath((*argv)[2], p);
        catDIR(p);
    }
}
