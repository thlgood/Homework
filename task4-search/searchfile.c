/*
   程序功能：从整个文件搜索某个字符所在的行，并将它所在的行的内容全部输出
argv[1]:待扫描的文件
argv[2]:待扫描的字符


   */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_LEN 10   //buf length
#define __NEW_LINE__    putchar('\n')
char* show_line(char *content, char *dst)
{
    int line_num = 1;
    char *flag = content;
    char *line_head = dst;
    while (flag != dst)
    {
        flag++;
        if (*flag == '\n')
            line_num++;
    }
    while (*line_head != '\n' && line_head != content)
        line_head--;

    printf("%d: ", line_num);
    line_head = (*line_head == '\n') ? line_head+1 : line_head;
    for (flag = line_head; *flag != '\n'; flag++)
        putchar(*flag);
    __NEW_LINE__;
    return flag+1;
}



int main(int argc, char *argv[])
{
    int file_d;                     //file descriptor
    char *ct_head;                  //content_first_char
    char *content;
    ssize_t read_len = BUF_LEN;     //had read length
    int mem_block_count = 0;

    file_d = open(argv[1], O_RDONLY);
    if (file_d < 0)
    {
        perror("open");
        exit (1);
    }

    content = ct_head = (char *) malloc(sizeof(char) * BUF_LEN);
    mem_block_count = 1;

    while (read_len == BUF_LEN)
    {
        read_len = read(file_d, ct_head, BUF_LEN);
        if (read_len < 0)
        {
            perror("read");
            exit(2);
        }
        if (read_len == BUF_LEN)
        {
            ct_head = (char *)realloc(content, sizeof(char) *(++mem_block_count) * BUF_LEN);
            if (ct_head == NULL)
            {
                perror("realloc");
                exit(3);
            }
            ct_head = &content[(mem_block_count-1) * BUF_LEN];
        }
        else
            ct_head[read_len] = '\0';
    }
    char *flag = content;
    char *dst = NULL;
    while (dst = strstr(flag, argv[2]))
    {
        flag = show_line(content, dst);
    }
    close(file_d);
    free(content);
    return 0;
}
