#include "Tshell.h"
#include "Process.h"

int main(int argc, char *argv[], char *envp[])
{
	init_arg(argc, argv);
	char Line[BUF_LEN];

	while (1) {
		INPUT_STD(Line);
		if (is_internal(Line)){
			run_internl(Line)
		}
		else {
			Process child;
			if (init_process(Line, &child) == false) {
				fputs("Can't found init this command!", stderr);
				continue;
			}
			child.pid = fork();
			if (child.pid < 0) {
				perror("fork()");
				continue;
			}
			if (child.pid) {
				if (run_mode == IS_DEBUG_MODE) {
					printf("调试模式:\n新进程PID:%d\n", child.pid);
				}
				add_to_PL(&child);
			}

			//如果该程序后台运行
			if ((!child.pid) && child.is_daemo) {
				printf("PID:%d\n", getpid());
				pid_t sid = setsid();
				if (sid < 0) {
					perror("setsid");
				}
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				close(STDERR_FILENO);
			}
			if (!child.pid) {
				execvp(child.vect[0], child.vect, envp);
			}
		}
	}
	return 0;
}
