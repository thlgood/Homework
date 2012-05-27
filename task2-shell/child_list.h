#ifndef CHILD_LIST
#define CHILD_LIST
#include "line_info.h"

struct child_list {
	char cmd[32];
	pid_t pid;
	struct child_list *next;
};

struct child_list *child = NULL, *child_list_tail = NULL;

struct child_list *add_to_child_list(struct line_info *line);
void show_all_child();

#endif
