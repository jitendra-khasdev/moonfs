#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "moon_mkfs.h"

int main(int argc, char *argv[])
{
	int fd, nr_block;
	struct stat *moon_disk;

	if (argc != 2){
		printf("Argument Missing:\n");
		exit(0);
	
	}

	fd  = open(argv[1], O_RDWR | O_CREAT, 755);


	/*
	 * Write a boot block on the disk.
	 */
	make_boot(fd, BOOT_BLOCK);
	make_sb(fd);
	make_block_bitmap(fd, block_bitmap);
	make_inode_bitmap(fd, inode_bitmap);
	nr_block = cal_inode_tblock(fd, 120);
	make_inode_table(fd, nr_block);
	nr_block = cal_block(fd);
	make_data_blocks(fd, nr_block);
	close(fd);

	return 0;
}
