#include "Tshell.h"
#include "Process.h"
#include "internal.h"
#include "PL.h"

int main(int argc, char *argv[], char *envp[])
{
	init_arg(argc, argv);
	char Line[BUF_LEN];
	signal_set();
	while (1) 
	{
		if (input(Line) == false)
		{
			continue;
		}
		if (is_internal(Line))
		{
			run_internal(Line);
		}
		else
		{
			Process child;
			if (init_process(Line, &child) == false) 
			{
				fputs("Can't found init this command!", stderr);
				continue;
			}
			child.pid = fork();
			if (child.pid < 0) 
			{
				perror("fork()");
				continue;
			}
			if (child.pid) 
			{
				if (run_mode == IS_DEBUG_MODE) 
				{
					printf("调试模式:\n新进程PID:%d\n", child.pid);
				}
				if (!add_to_PL(&child))
				{
					perror("add_to_PL");
				}
				if (!child.is_daemon)
				{
					int status;
					pid_t pid = wait(&status);
					del_from_PL(pid);
				}
			}

			//如果该程序后台运行
			if ((!child.pid) && child.is_daemon) 
			{
				pid_t sid = setsid();
				if (sid < 0) 
				{
					perror("setsid");
				}
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				close(STDERR_FILENO);
			}
			if (!child.pid) 
			{
				execvp(child.vect[0], child.vect);
				perror("execvp");
				exit(1);
			}
			clean_process(&child);
		}
	}
	return 0;
}
