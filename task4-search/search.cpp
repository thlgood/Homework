#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "head.h"

#define BUF_LEN 1000   //buf length

int search(const char *file_path, const char *id)
{
    int file_d;                     //file descriptor
    char *flag = content;
    char *dst = NULL;
    char *ct_head;                  //content_first_char
    char *content;
    ssize_t read_len = BUF_LEN;     //had read length
    int line = 0;
    int mem_block_count = 1;

    file_d = open(file_path, O_RDONLY);
    if (file_d < 0)
    {
        perror("open");
        return 0;
    }

    content = ct_head = (char *) malloc(BUF_LEN * mem_block_count++);

    while (read_len == BUF_LEN)
    {
        read_len = read(file_d, ct_head, BUF_LEN);
        if (read_len < 0)
        {
            perror("read");
            goto end;
        }
        if (read_len == BUF_LEN)
        {
            ct_head = (char *)realloc(content, (mem_block_count++) * BUF_LEN);
            if (ct_head == NULL)
            {
                perror("realloc");
                goto end;
            }
            ct_head = &content[(mem_block_count-1) * BUF_LEN];
        }
        else
            ct_head[read_len] = '\0';
    }
    
    
    if ((dst = strstr(content, id)) != NULL)
    {
        line = 1;
        while (flag != dst)
        {
            line = (*flag == '\n') ? line+1 : line;
            flag++;
        }
    }
end:
    close(file_d);
    free(content);
    return line;
}
#undef BUF_LEN
