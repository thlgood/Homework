#include "Tshell.h"
#include "PL.h"
#include <signal.h>
#include <unistd.h>

/*
 *收到SIGCHLD信号之后的回调函数
 */
static void wait_child(int sig_type)
{
	int status;
	pid_t pid = wait(&status);
	del_from_PL(pid);
}

/*
 *设置信号，当子进程退出的时候会收到SIGCHLD信号
 */
void signal_set()
{

	if (signal(SIGCHLD, wait_child) == SIG_ERR) {
		perror("Signal");
		exit(EXIT_FAILURE);
	}
}
