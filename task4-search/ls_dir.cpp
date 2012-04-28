#include <unistd.h>
#include <sys/param.h>  //for PATH_MAX
#include <limits.h>     //for realpath
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

void ls_dir(const char *resolved_path)
{
    struct dirent *entry;
    struct stat stat_buf;
    DIR *dp;
    if (resolved_path == NULL)
    {
        fputs("resolved_path == NULL\n", stderr);
        return;
    }
    dp = opendir(resolved_path);
    if (dp == NULL)
    {
        fputs(resolved_path, stderr);
        return;
    }
    while ((entry = readdir(dp)) != NULL)
    {
        struct stat stat_buf;
        char path_temp[PATH_MAX];
        memcpy(path_temp, resolved_path, PATH_MAX);
        if (strcmp(entry->d_name,  ".") &&
            strcmp(entry->d_name, ".."))
        {

            strcat(path_temp, "/");
            strcat(path_temp, entry->d_name);
            lstat(path_temp, &stat_buf);

            if (S_ISDIR(stat_buf.st_mode))
                ls_dir(path_temp);
            else
            {
                string path_str(path_temp);
                all_paths.push_back(path_str);
            }
        }
    }
    free(dp);
}
