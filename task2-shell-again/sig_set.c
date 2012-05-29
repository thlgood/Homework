#include "Tshell.h"
#include <signal.h>
#include <unistd.h>

static void wait_child(int sig_type)
{
	int status;
	pid_t pid = wait(&status);
}

void signal_set()
{

	if (signal(SIGCHLD, wait_child) == SIG_ERR) {
		perror("Signal");
		exit(EXIT_FAILURE);
	}
}
