#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>

#include <linux/fs.h>
#include <linux/ext2_fs.h>

#define FS	"../fs"
typedef struct ext2_super_block ext2_sb;

int main()
{
	int fd = open(FS, O_RDONLY);
	assert (fd > 0);
	ext2_sb sb_block;

	lseek(fd, 1024, SEEK_CUR);
	read(fd, &sb_block, sizeof(ext2_sb));
	
	printf("%d\n", sb_block.s_blocks_count);
	close(fd);
	return 0;
}
