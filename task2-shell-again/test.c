#include "Tshell.h"
#include "internal.h"
#include "Process.h"
/*int main(int argc, char *argv[])
{
	char cmd[1024];
	while (IN_STD(cmd) && strcmp(cmd, "exit")) {
		if (is_internal(cmd)){ 
			run_internal(cmd);
		}
		else {
			puts("false");
		}
	}
//	system("env");
	return 0;
}*/

int main(int argc, char *argv[], char *envp[])
{
/*	char cmd[BUF_LEN];
	fgets(cmd, BUF_LEN, stdin);*/
	char cmd[] = {"ls"};

	Process child;
	init_process(cmd, &child);
	printf("%s\n", child.vect[0]);
	child.pid = fork();
	if (child.pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (!child.pid) {
		if (execvp(child.vect[0], child.vect) < 0)
/*		char *vec[] = {"ls", (char*)0};
		if (execvp("ls", vec) < 0)*/
			perror("execv");
	}
	if (child.pid) {
		int status;
		wait(&status);
	}
	return 0;


}
