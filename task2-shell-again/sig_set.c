#include "Tshell.h"
#include "PL.h"
#include <signal.h>
#include <unistd.h>

static void wait_child(int sig_type)
{
	int status;
	pid_t pid = wait(&status);
	del_from_PL(pid);
	/*
	if (del_from_PL(pid) != true)
	{
		fprintf(stderr, "DELETE %d from PL was failure!\n", pid);
	}*/
}

void signal_set()
{

	if (signal(SIGCHLD, wait_child) == SIG_ERR) {
		perror("Signal");
		exit(EXIT_FAILURE);
	}
}
