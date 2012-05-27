#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "myshell.h"
#include <string.h>
#include <fcntl.h>
#include <singal.h>

#define PS2		"> "
#define OUTPUT(arg)	printf("> %s", arg)
#define INPUT(line)	fgets(line, 1024, stdin)

int main(int argc, char *argv[], char **envp)
{
	char line[1024];	//行缓冲
	if (argc != 1 && !strcmp(argv[2], "-v")) {
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0) {
			strerror(errno);
			exit (1);
		}
		freopen(argv[1], "r", "stdin");
	}

	while (1)
	{

		OUTPUT("");
		INPUT(line);
//		OUTPUT(line);
		struct line_info this_line;
		parser_line(line, &this_line);

		if (this_line.is_internal)
		{
			run_internal(&this_line, envp);
		}
		else if (!this_line.is_internal) {
			signal(SIGCHID, wait_child);

			this_line.pid = fork();
			if (pid < 0) {
				perror("fork");
				continue;
			}
			else {
				if (this_line.pid != 0) {
					add_to_child_list(&this_line);
				}
				else {
					//Wrap exec
					run_external(&this_line);
				}
			}

		}
		else {
			fputs("Can't parser this command!\n", stderr);
			continue;
		}
	}

	return 0;
}
