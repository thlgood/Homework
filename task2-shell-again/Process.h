#ifndef PROCESS_H
#define PROCESS_H
#include "Tshell.h"

typedef struct
{
	char **vect;
	pid_t pid;
	bool is_daemon;
}Process;

bool init_process(char *Line, Process *child);
void clean_process(Process *child);

#endif
