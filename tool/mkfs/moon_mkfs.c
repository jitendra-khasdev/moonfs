#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moon_mkfs.h"

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
	long int pos;

	/*Seek for the boot block*/
	pos = lseek (fd, boot_size, SEEK_SET);
	
	printf("Boot Block End == %ld\n", pos);
	return pos;

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
	int pos, end_pos, nr_blocks;

	pos = lseek(fd, 0, SEEK_CUR);
	end_pos = lseek(fd, 0, SEEK_END);

	nr_blocks = ( end_pos - pos ) / BLOCK_SIZE;

	pos = lseek(fd, pos, SEEK_SET);

	return nr_blocks;
}

/*
 * make_sb : This function is used to create super block on the disk just after
 * boot block.
 * 
 * args: fd - file descriptor, *sb - pointer to super block
 * return 0;
 *
 */
int make_sb(int fd)
{
	struct super_block *sb;
	char *zero_buf;
	int ret_byte, rem_byte;

	sb = (struct super_block *)malloc(sizeof(struct super_block));

	sb->name = "moonfs";
	sb->size = 234;
	sb->block_count = 345;

	ret_byte = write(fd, sb, sizeof(struct super_block));

	if (ret_byte < 0){
		printf("Unable to write super block\n");
	}

	rem_byte = BLOCK_SIZE-ret_byte;
	zero_buf = (char *)malloc(sizeof(char)*(rem_byte));

	memset(zero_buf, 0, rem_byte);

	write(fd, zero_buf, rem_byte);

	free(zero_buf);
	free(sb);
	printf("Super Block End == %ld\n", lseek(fd, 0, SEEK_CUR));
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
	int ret_byte;
	
	ret_byte = write(fd, block_bitmap, BLOCK_SIZE);

	printf("Block Bitmap End == %ld\n", lseek(fd, 0, SEEK_CUR));

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

int make_inode_bitmap(int fd, char *inode_bitmap)
{
	int ret_byte;
	
	ret_byte = write(fd, inode_bitmap, BLOCK_SIZE);

	printf("Inode Bitmap End == %ld\n", lseek(fd, 0, SEEK_CUR));
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
	int pos, end_pos, nr_blocks, inode_table_blocks;

	pos = lseek(fd, 0, SEEK_CUR);
	
	end_pos = lseek(fd, 0, SEEK_END);
	
	pos = lseek(fd, pos, SEEK_SET);

	nr_blocks = (end_pos - pos) / BLOCK_SIZE ;
	
	inode_table_blocks = (nr_blocks * 10) / 100;

	printf("inode table blocks == %d\n", inode_table_blocks);

	return inode_table_blocks;
}

/*
 * make_inode_table : This function is used to create inode table.
 * args : fd - file descriptor
 * return : 0 if success
 */

int make_inode_table (int fd, int num_blocks)
{
	int num, i, rem, j;
	struct inode inode;
	char *temp;
	j = 0;
	while (j < num_blocks) {
		for (i = sizeof(inode); i < (BLOCK_SIZE); i += num) {
			num = write(fd, &inode, sizeof(inode));
		}

		rem = (BLOCK_SIZE - (i - num));
		if ( rem > 0 ) {
			temp = (char *) calloc(rem, sizeof(char));
			write(fd, temp, rem);
			free(temp);
		}

		j++;
	}	
	printf("Inode Table End == %ld\n", lseek(fd, 0, SEEK_CUR));

}

/*
 * make_data_blocks : This function is used to create this function
 *
 */
int make_data_blocks (int fd, int nr_blocks)
{
	char *buffer;
	int i;

	buffer = (char *)calloc(4096, sizeof(char));

	i = 0;

	for ( i = 0; i < nr_blocks; i++ ) {
		write(fd, buffer, BLOCK_SIZE);
	}
	
	printf("Data Blocks End == %ld\n", lseek(fd, 0, SEEK_CUR));
	printf("Your filesystem successfully created\n");
	return 0;
}
