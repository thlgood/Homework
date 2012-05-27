#include "Ts_PL.h"

//extern PL *PL_head, PL

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
