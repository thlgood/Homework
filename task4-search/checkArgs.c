#include "head.h"
#include <string>

extern int thread_count;
extern char *all_paths;

void checkArgs(int &argc, char &argv[][])
{
    thread_count = 1;
    if (argc < 3)
    {
        fputs("Too argument!", stderr);
        exit(1);
    }
    if (argv[1] == "-j")
        thread_count = argv[2];

}
