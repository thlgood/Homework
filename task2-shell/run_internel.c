#include "myshell.h"
#include "help.h"
#include "cd.h"
#include "child_list.h"

void run_internal(struct line_info *p, char **envp)
{
	if (!strcmp("cd", p->cmd)){
		if (chdir(p->arg))
			perror("chdir:");
	}
	else if(!strcmp("echo", p->cmd)) {
		printf("%s\n", p->arg);
	}
	else if (!strcmp("help", p->cmd)) {
		help();
	}
	else if (!strcmp("environ", p->cmd)) {
		for (; *envp != NULL; envp++)
			printf("%s\n", *envp);
	}
	else if (!strcmp("jobs", p->cmd)) {
		show_all_child();
	}
	else if (!strcmp("quit", p->cmd) || 
	         !strcmp("exit", p->cmd) ||
			 !strcmp("bye",  p->cmd)) {
		fputs("Bye!\n");
		exit(0);
	}
	else {
		fprintf(stderr, "UNKNOW INTERNAL CMD: %s\n", p->cmd);
	}
}
