#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
	char **env;
	for (env = envp; *env != NULL; env++)
		printf("%s\n", *env);
	return 0;
}
