#include <unistd.h>
#include <limits.h>     //for realpath
#include <stdlib.h>
#include <stdio.h>      //perror
#include <string.h>
#include "head.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/param.h>  //for PATH_MAX

#include <vector>
#include <string>

using namespace std;

void catDIR(const char *re_path)
{
    DIR *dp;
    struct stat file_info;
    struct dirent *entry;

    if ((dp = opendir(re_path)) == NULL)
    {
        perror("opendir");
        return;
    }
    while (entry = readdir(dp))
    {
        if (entry->d_name[0] == '.')
            continue;
        
        char next_path[PATH_MAX];
        strcpy(next_path, re_path);
        strcat(next_path, "/");
        strcat(next_path, entry->d_name);
        
        lstat(next_path, &file_info);
        
        if (S_ISDIR(file_info.st_mode))
        {
            catDIR(next_path);
        }
        else
        {
            string temp(next_path);
            all_paths.push_back(temp);
        }
    }
    closedir(dp);
    free(entry);
}
