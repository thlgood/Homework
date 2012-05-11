#ifndef _LINE_INFO_
#define _LINE_INFO_
#include <stdbool.h>
#include <unistd.h>

struct line_info
{
	char cmd[64];
	char arg[1024-64];
	bool is_internal;
	bool is_demo;
	pid_t pid;
};
#endif
