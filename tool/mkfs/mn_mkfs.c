#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define BLOCK_SIZE 4096
#define BOOT_BLOCK 1024

struct super_block {
	char *name;
	int size;
	int block_count;
};


struct inode {
	int blocks;
	int ptr[10];
};

char block_bitmap[BLOCK_SIZE];
char inode_bitmap[BLOCK_SIZE];

/*
 * create_block : This function creates block on the disk as specified byte.
 * fd : File Descriptor
 * byte : Number of bytes for the block
 * return : Number of byte seeked
 */

int seek_byte (int fd, int byte)
{
	long int pos, cur_pos;

	pos = 0;
	pos = (long int) lseek (fd, 0, SEEK_CUR);
	printf("Current seek position == %ld\n", pos);

	/*Seek for the boot block*/
	pos = lseek (fd, byte, SEEK_SET);
	
	cur_pos = lseek (fd, 0, SEEK_CUR);
	printf("Now seek position == %ld\n\n", cur_pos);
	return cur_pos;
}

int create_super_block (int fd, int pos)
{
	int cur_pos, len, temp;
	struct super_block sb;
	
	cur_pos = lseek(fd, 0, SEEK_CUR);

	if (cur_pos != pos) {
		printf("Offset mismatched\n");
		return -1;
	}

	len = write(fd, &sb, sizeof(sb));

	printf("len == %d\n", len);
	cur_pos = -1;
	
	if (len > 0)
		cur_pos = seek_byte(fd, BLOCK_SIZE - len);
	
	return cur_pos;
}

int create_bitmap (int fd, char *bitmap)
{
	
	int cur_pos, len, temp;

	cur_pos = lseek(fd, 0, SEEK_CUR);
	
	temp = BOOT_BLOCK + 2*BLOCK_SIZE;

	printf("cur_pos == %d and temp == %d", cur_pos, temp);
	if (cur_pos !=  (BOOT_BLOCK + 2*BLOCK_SIZE)) {
		printf("Error in creating bitmap\n");
		return -1;
	}

	len = write(fd, bitmap, BLOCK_SIZE);
	
	if (len != BLOCK_SIZE) {
		printf("Error in creating bitmap \n");
		return -1;
	}

	return len;
}

int main(int argc, char *argv[])
{
	int fd, len;
	off_t pos;

	struct inode in;

	if (argc != 2){
		printf("Argument Missing:\n");
		exit(0);
	
	}

	fd = open(argv[1], O_WRONLY);

	pos = 0;
	printf("Creating [Boot Block] at %ld\n", pos);
	/*Seek for the boot block*/
	pos = seek_byte(fd, BOOT_BLOCK);
	
	/*Create super block and allocate it 4K*/
	printf("Creating [Super Block] at %ld\n", pos);
	create_super_block(fd, pos);
	
	/*Create a block bit map*/
	create_bitmap(fd, block_bitmap);

	/*Create a inode bitmap*/
	len = write(fd, &inode_bitmap, sizeof(inode_bitmap));
	pos = lseek(fd, BLOCK_SIZE, SEEK_SET);
	printf("Seek == %d \n", (int)pos);


	return 0;
}
