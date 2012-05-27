#include "myshell.h"
#include "child_list.h"

#define MALLOC_CHILD_LIST (struct child_list *)malloc(sizeof(struct child_list))

extern struct chld_list child, child_list_tail;

void show_all_child(){
	struct child_list *temp = child;
	printf("Child process:\n");
	while (temp){
		printf("%s\t%d\n", temp->cmd, temp->pid);
		temp = temp->next;
	}
}

struct child_list *add_to_child_list(struct line_info *line)
{
	struct line_info *node = MALLOC_CHILD_LIST;

	if (!node) {
		return NULL;
	}
	else {
		node->pid = line->pid;
		strcpy(node->cmd, line->cmd);
		node->next = NULL;
	}

	//Insert to child_list
	if (child_list_tail == NULL) {
		child_list_tail = child = node;
	}
	else {
		child_list_tail->next = node;
		child_list_tail = node;
	}
	return node;
}
