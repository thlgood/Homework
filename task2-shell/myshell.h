#ifndef _MYSHELL_H_
#define _MYSHELL_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "line_info.h"
#include <string.h>

extern const char internal;

bool help();
void wait_child(int sig_type);

#endif
