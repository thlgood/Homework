#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//分析参数，确定要搜索的目录、关键字和线程数
void checkArgs(int *argc, char ***argv);
//遍历目录，获取目录内文件的所有路径
void catDIR(const char *re_path);
//搜索
void *autosearch(void *args_no_use);

int search(const char *file_path, const char *id);

//所有文件的目录
extern std::vector<std::string>all_paths;
//关键字
extern std::string id;
//互斥锁
extern pthread_mutex_t paths_mutex;
//线程总数
extern int pthread_count;

#endif
