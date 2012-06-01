#ifndef TSHELL_H
#define TSHELL_H

//standard header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define PS2           "> "
#define BUF_LEN       1024

#define NOT_DEBUG_MODE true
#define	IS_DEBUG_MODE  false

void init_arg(int argc, char *argv[]);
void signal_set();
bool input(char *line);
extern bool run_mode;

#endif
