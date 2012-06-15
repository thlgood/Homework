/*
 *全局变量：PL表头，PL表尾和运行模式
 */

#include "PL.h"
#include <stdbool.h>

PL *PL_head = NULL;
PL *PL_tail = NULL;

//run_mode是否为调试模式
bool run_mode = NOT_DEBUG_MODE;
