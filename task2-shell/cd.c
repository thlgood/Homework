/*
 *作者：唐恒亮
 *日期：2012-5-8
 *描述：改变工作目录并改变环境变量
 */

#include <unistd.h>
#include "myshell.h"
#include <limits.h>	// for PATH_MAX macro
#include <errno.h>


/* 
 * 原型：char *cd(const char *path)
 * 参数：path 目的地的相对/绝对路径
 * 返回：目的地的绝对路径
 * 错误：出错会返回NULL，并输出错误信息，但是不修改errno的值
 */

void cd(const char *path)
{
	int errno_temp = errno;
	char abs_path[PATH_MAX];

	if (realpath(path, abs_path) == NULL)
	{
		strerror(errno);
		errno = errno_temp;
		return;
	}

	if (!chdir(abs_path))
	{
		strerror(errno);
		errno = errno_temp;
		return;
	}
}
