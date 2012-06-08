#include "common.h"


/*Read ext2 super block
 *
 *sb_block: ext2_sb
 *filepath: 文件路径
 *
 */

ext2_sb* read_sb(ext2_sb *sb_block, const char* filepath)
{
	if (NULL == sb_block)
	{
		return NULL;
	}

	int fd = open(FS, O_RDONLY);
	assert (fd > 0);

	lseek(fd, BLOCK_SIZE, SEEK_CUR);
	read(fd, sb_block, sizeof(ext2_sb));
	
	close(fd);
	return sb_block;
}
