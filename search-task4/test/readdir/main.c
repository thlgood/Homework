#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


void scan_dir(const char *directory);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error!nUsage:%s pathn", argv[0]);
        return 1;
    }
    scan_dir(argv[1]);
    return 0;
}

void scan_dir(const char *directory)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    
    if((dp = opendir(directory)) == NULL)
    {
        perror("opendir");
        return;
    }
    fputs(directory, stderr);
    chdir(directory);

    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {

            if (entry->d_name[0] != '.') /*&& 
                    (strcmp(entry->d_name, "..") != 0) && 
                    (entry->d_name[0] != '.'))*/
            {
                printf("%s/", getcwd(NULL, 0));
                printf("%s/n", entry->d_name);
                scan_dir(entry->d_name);
            }
        }
        else
        {
            if (entry->d_name[0] != '.')
            {
                printf("%s/", getcwd(NULL, 0));
                printf("%s\n", entry->d_name);
            }
        }
    }
    chdir("..");
    closedir(dp);
}
