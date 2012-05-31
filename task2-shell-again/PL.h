#ifndef TS_PL_H
#define TS_PL_H

#include "Tshell.h"
#include "Process.h"


//--------------- Process ----------------
//PL:Process List
struct PL
{ 
	pid_t pid;
	char cmd[32];
	char **vect;	//String to vect for execvp
	struct PL *next;
};
typedef struct PL PL;

// malloc PL
#define MALLOC_PL	(PL *)malloc(sizeof(PL))
extern PL *PL_head;
extern PL *PL_tail;

void show_PL();
bool add_to_PL(Process *child);
bool del_from_PL(pid_t pid);
void free_PL();
#endif
