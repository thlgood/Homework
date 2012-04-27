#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    struct stat buf;
    lstat(argv[1], &buf);
    if (S_ISDIR(buf.st_mode))
        printf("%s\n", argv[1]);
    return 0;
}
