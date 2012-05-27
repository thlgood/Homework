#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int agc, char *argv[], char *envp[])
{
	char line[1024];
//	char *p = &line[0];
	pid_t son = -1;
	fgets(line, 1024, stdin);
	son = fork();
	if(son < 0) {
		exit(EXIT_FAILURE);
	}
	else {
		if (son == 0) {
			execl("./argv", line, (char *)0);
		}
		else {
			int status;
			wait(&status);
		}
	}
	return 0;
}
