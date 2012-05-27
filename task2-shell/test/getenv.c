#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *path = "PATH";
	printf("PATH:%s\n", getenv(path));
	printf("PID:%s\n", getenv("PID"));
	return 0;
}
