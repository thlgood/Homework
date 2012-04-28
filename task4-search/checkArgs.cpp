#include "head.h"
#include <string>

/*extern int thread_count;
extern char *all_paths;*/

void checkArgs(int &argc, char ***argv)
{
    int searched = 0;
    paths_mutex = PTHREAD_MUTEX_INITIALIZER;
    thread_count = 1;
    if (argc < 3)
    {
        fputs("Too argument!", stderr);
        exit(1);
    }
    if (argv[1] == "-j")
    {
        thread_count = argv[2];
        id = *argv[3];
        ls_dir(*argv[4]);
    }
    else
    {
        id = *argv[1];
        ls_dir(*argv[2]);
    }

}
