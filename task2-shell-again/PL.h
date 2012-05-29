#ifndef TS_PL_H
#define TS_PL_H
#include "Tshell.h"


//--------------- Process ----------------
//PL:Process List
struct PL { 
	pid_t pid;
	char cmd[32];
	char **vect;	//String to vect for execvp
	struct PL *next;
};
typedef struct PL PL;

// malloc PL
#define MALLOC_PL	(PL *)malloc(sizeof(PL))

//Process List head & tail
PL *PL_head = NULL;
PL *PL_tail = NULL;

void show_PL();
bool add_to_PL(Process *child);
bool free_PL();
#endif
