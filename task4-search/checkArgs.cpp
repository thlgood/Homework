#include "head.h"
#include <string>
#include <string.h>


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
    if (!strcmp(*argv[1],  "-j"))
    {
        pthread_count = (int)(*argv[2][0]- '0');
        id = *argv[3];
        ls_dir(*argv[4]);
    }
    else
    {
        id = *argv[1];
        ls_dir(*argv[2]);
    }

}
