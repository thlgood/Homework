#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void wait_child(int sig_type)
{
	int status;
	pid_t pid = wait(&status);
}
