#include "PL.h"
#include "Process.h"

void show_PL()
{
	PL *temp = PL_head;
	if (PL_head == NULL)
		return;

	printf("CMD           PID\n");
	while (temp != NULL) {
		printf("%-14s%d\n", temp->cmd, temp->pid);
		temp = temp->next;
	}
}

bool add_to_PL(Process *child)
{
	PL *temp = MALLOC_PL;
	if (temp == NULL)
		return false;

	temp->pid = child->pid;
	strcpy(temp->cmd, *(child->vect));
	temp->next = NULL;

	if (PL_head == NULL) {
		PL_head = PL_tail = temp;
	}
	else {
		PL_tail = temp;
		PL_tail = PL_tail->next;
	}
	return true;
}

void free_PL() {
	PL *temp;
	while (PL_head != NULL){
		temp = PL_head->next;
		free(PL_head);
		PL_head = temp;
	}
}
