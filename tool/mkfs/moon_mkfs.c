/*
 * make_boot : This function is used to create bootblock for on disk. Generally
 * size of 1024 Byte.
 *
 * args: fd - file descriptor,  boot_size - Boot size in byte
 * return: 0 if sucessful, -1 on error 
 *
 */

int make_boot(int fd, int boot_size)
{

	return 0;
}

/*
 * cal_block : This function is used to calculate no. of blocks with rest space
 * on the disk (expect boot_size)
 *
 * args: fd - file descriptor
 * return: 0 if success, -1 on error
 *
 */

int cal_block(int fd)
{

	return 0;
}

/*
 * make_sb : This function is used to create super block on the disk just after
 * boot block.
 * 
 * args: fd - file descriptor, *sb - pointer to super block
 * return 0;
 *
 */
int make_sb(int fd, struct super_block *sb)
{

	return 0;
}

/*
 * make_block_bitmap : This function is used to create block bitmap block on 
 * the disk just after super block.
 * 
 * args: fd - file descriptor, *block_bitmap - pointer to super block
 * return 0;
 *
 */

int make_block_bitmap(int fd, char *block_bitmap)
{

	return 0;
}

/*
 * make_inode_bitmap : This function is used to create inode bitmap block on 
 * the disk just after block bitmap block.
 * 
 * args: fd - file descriptor, *inode_bitmap - pointer to super block
 * return 0;
 *
 */

int make_block_bitmap(int fd, char *inode_bitmap)
{

	return 0;
}

/*
 * make_inode_bitmap : This function is used to create inode bitmap block on 
 * the disk just after block bitmap block.
 * 
 * args: fd - file descriptor, *inode_bitmap - pointer to super block
 * return 0;
 *
 */

int make_block_bitmap(int fd, char *inode_bitmap)
{

	return 0;
}

/*
 * cal_inode_tblock : This function is used to calculate no of block that will
 * contain inode table.
 *
 * args: fd - file descriptor
 * return 0;
 *
 */
int cal_inode_tblock(int fd, long int seek_pos)
{

	return 0;
}
