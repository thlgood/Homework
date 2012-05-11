#include "run_external.h"
#include "myshell.h"
#include <unistd.h>
#include "line_info.h"

void run_external(struct line_info *p)
{
	if (p->is_demo)
	{
		pid_t pid_demo;
		pid_demo = fork();
		if (pid_demo == 0)
		{
			setsid();
			execlp(p->cmd, p->cmd, p->arg, NULL);
		}
		else
		{
			printf("%s was run in PID: %lu" p->cmd, p->pid);
			exit(0);
		}
	}
	else
	{
		execlp(p->cmd, p->cmd, p->arg, NULL);
	}
}

