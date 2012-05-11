#include "parser_line.h"
#include <stdbool.h>
#include "myshell.h"

#define _INTERNAL_COUNT_	8
struct line_info *parser_line(char *line_start, struct line_info *p)
{
	sscanf(line_start, "%s%s", p->cmd, p->arg);	//init p->cmd
	p->is_internal = false;				//init p->is_internal with default value
	p->is_demo = false;				//init p_>is_demo

	//init p->is_internal
	int internal_count = 0;
	for (; internal_count < _INTERNAL_COUNT_; internal_count++)
	{
		if (!strcmp(internal[internal_count]))
		{
			p->is_internal = true;
			break;
		}
	}
	return p;
}

#undef _INTERNAL_COUNT_
