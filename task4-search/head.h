#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//void search(const char* path);
//int search(const char *file_path, const char *id)
void checkArgs(int *argc, char ***argv);
void catDIR(const char *re_path);
void *autosearch(void *args_no_use);

int search(const char *file_path, const char *id);


extern std::vector<std::string>all_paths;
extern std::string id;
extern pthread_mutex_t paths_mutex;
extern int pthread_count;

#endif
