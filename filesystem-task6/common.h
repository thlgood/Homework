#ifndef COMMON_H
#define COMMON_H

#include <linux/fs.h>
#include <linux/ext2_fs.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>
#include <fcntl.h>
#include <errno.h>

#define BLOCK_SIZE	1024
#define FILE_SYSTEN "fs"

typedef struct ext2_super_block ext2_sb;

ext2_sb* read_sb(ext2_sb *sb_block, const char* filepath);

#endif
