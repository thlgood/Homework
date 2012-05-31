#include "Tshell.h"
#include "internal.h"
#include "PL.h"
#include <unistd.h>

bool is_internal(const char *p)
{
	char buf[BUF_LEN];
	sscanf(p, "%s", buf);
	if (strcmp(buf, "cd")   &&
	    strcmp(buf, "env")  &&
	    strcmp(buf, "echo") &&
	    strcmp(buf, "help") &&
	    strcmp(buf, "quit") &&
	    strcmp(buf, "bye")  &&
	    strcmp(buf, "exit") &&
	    strcmp(buf, "jobs"))
    	{

		return false;
	}
	else 
    	{
		return true;
	}
		
}

bool run_internal(char *p)
{
	char cmd[16];
	sscanf(p, "%s", cmd);

	char *cmd_addr;
	char *arg;
	cmd_addr = strstr(p, cmd);
	if (cmd_addr == NULL)
   	{
		perror("strstr");
		return false;
	}

	arg = cmd_addr + strlen(cmd);
	while ((*arg == ' ' || *arg == '\t') && (*arg != '\0'|| *arg != '\n'))
   	{
		arg++;
	}
	if (*arg == '\0' || *arg == '\n')
    	{
		arg = NULL;
	}

	if (!strcmp(cmd, "cd"))
    	{
		if (arg != NULL)
		{
			if (chdir(arg) != 0)
		    {
				perror("chdir");
				return false;
			}
		}
	}
	else if (!(strcmp(cmd, "exit") && strcmp(cmd, "bye") && strcmp(cmd, "quit")))
   	{
		fputs("Bye\n", stdout);
		exit(EXIT_SUCCESS);
	}
	else if (!(strcmp(cmd, "echo")))
   	{
		if (NULL != arg)
			printf("%s", arg);
		else
			fputs("\n", stdout);
	}
	else if (!strcmp(cmd, "jobs"))
   	{
		show_PL();
	}
	else if (!strcmp(cmd, "env"))
   	{
		system("env");
	}
	else if (!strcmp(cmd, "help"))
   	{
		FILE *help_p = fopen("help_msg", "r");
		if (help_p == NULL)
		{
			perror("help_p");
			return false;
		}
		char buf[1024];
		while (fgets(buf, 1024, help_p))
			fputs(buf, stdout);
		fclose(help_p);
	}
	else
    	{
		printf("unknow internal cmd;%s\n", cmd);
		return false;
	}
	return true;
}
