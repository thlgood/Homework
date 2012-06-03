#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
#define BUF_LEN    1000
/*int main(int argc, char *argv[])
{
    int line = search(argv[1], argv[2]);
    if (line > 0)
        printf("%d\n", line);
    return 0;
}*/

int search(const char* file_path, const char *key)
{
    int mem_block = 0;
    int line_num = -1;
    int statu = 1;
    FILE *file_p;
    char *BUF = NULL;
    char *flag = NULL;

    if ((file_p = fopen(file_path, "r")) == NULL)
        return 0;
    while(statu)
    {
        mem_block = 0;
        flag = BUF = (char *)realloc(BUF, BUF_LEN * ++mem_block);
        while ((*flag = fgetc(file_p)) && *flag != '\n' && *flag != EOF)
        {
            if (flag + 1 == &BUF[BUF_LEN * mem_block])
            {
                BUF = (char *)realloc(BUF, BUF_LEN * ++mem_block);
                flag = &BUF[BUF_LEN* ( mem_block-1 ) - 1];
            }
            flag++;
        }
        if (*flag == EOF)
            break;

        *flag = '\0';
        if (strstr(BUF, key) != NULL)
        {
            line_num *= -1;
            break;
        }

        free(BUF);
        BUF = NULL;
        line_num--;
    }
    free(BUF);
    fclose(file_p);
    return line_num;
}
