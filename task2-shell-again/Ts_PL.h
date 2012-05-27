#ifndef TS_PL_H
#define TS_PL_H
#include "Tshell.h"


//--------------- Process ----------------
//PL:Process List
struct PL { 
	pid_t pid;
	char cmd[32];
	struct PL *next;
};
typedef struct PL PL;

// malloc PL
#define MALLOC_PL	(PL *)malloc(sizeof(PL))

//Process List head & tail
PL *PL_head = NULL, PL_tail = NULL;

void show_PL();

#endif
