/*
 *
 *内部命令：内部命令模块包含两部分，一部分判断用户输入的是否为
 *内部命令，第二部分为执行用户输入的内部命令
 */
#ifndef INTERNAL_H
#define INTERNAL_H

#include "Tshell.h"

bool is_internal(const char *p);
bool run_internal(char *p);

#endif
