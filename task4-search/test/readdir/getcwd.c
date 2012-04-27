#include <unistd.h>
#include <stdio.h>
int main()
{
    printf("%s\n", getcwd(NULL, 0));
    return 0;
}
