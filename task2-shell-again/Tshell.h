#ifndef TSHELL_H
#define TSHELL_H

//standard header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PS2           "> "
#define BUF_LEN       1024
#define INPUT(a, b)   puts(PS2); \
                      fgets(a, BUF_LEN, b);

#define INPUT_STD(a)  puts(PS2); \
                      fgets(a, BUF_LEN, stdin);

#endif
