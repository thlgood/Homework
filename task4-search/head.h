#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>

void search(const char* path);

void checkArgs(int *argc, char ***argv);
void ls_dir(const char *resolved_path);
int search(const char *file_path, const char *id);
void autosearch();

/*extern int thread_count;
extern char *path;*/

#endif
