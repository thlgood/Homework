#include "Tshell.h"
#include "Process.h"

static char** vecting(char *dst_string)
{
	char *cstring = (char *)malloc((strlen(dst_string) + 1));
	char *flag = cstring;
	strcpy(cstring, dst_string);
 
	int w_count = 0;       //word count
	int v_count = 0;       //vector count
 
	while (*flag != '\0') {
		if (*flag == ' ' || *flag == '\n' || *flag == '\t') {
			*flag = '\0';
			flag++;
		}
		else {
			w_count++;
			while (*flag != ' '  &&
			       *flag != '\n' &&
			       *flag != '\t' &&
			       *flag != '\0')
				flag++;
		}
	}
 
	char **cvector = (char **)malloc(sizeof(char *)*(w_count+1));
	cvector[w_count] = NULL;
 
	for (flag = cstring; v_count < w_count; v_count++) {
		while (*flag == '\0') {
			flag++;
		}
		cvector[v_count] = flag;
		while (*flag != '\0') {
			flag++;
		}
	}
	return cvector;
}

bool init_process(char *Line, Process *child)
{
	char **temp = child->vect = vecting(Line);
	if (temp == NULL) {
		return false;
	}
	while (*(temp+1) != NULL)
		temp++;
	if (!strcmp(*temp, "&"))
		child->is_daemon = true;
	else
		child->is_daemon = false;
	return true;
}

void clean_process(Process *child)
{
	free(child->vect);
}
