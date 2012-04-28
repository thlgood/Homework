#include <sys/param.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char path_buf[PATH_MAX];
    char *path_p;
    path_p = realpath(argv[1], path_buf);
    printf("path_buf =%s\n", path_buf);
    printf("path_p   =%s\n", path_p);
    //free(path_p);
    return 0;
}
