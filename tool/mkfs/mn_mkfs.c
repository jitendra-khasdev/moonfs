#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define BLOCK_SIZE 4096

struct super_block {
	char *name;
	int size;
	int block_count;
};


struct inode {
	int blocks;
	int ptr[10];
};



int main(int argc, char *argv[])
{
	int fd, len;
	off_t pos;
	char block_bitmap[BLOCK_SIZE];
	char inode_bitmap[BLOCK_SIZE];

	struct super_block sb;
	struct inode in;

	if (argc != 2){
		printf("Argument Missing:\n");
		exit(0);
	
	}

	fd = open(argv[1], O_WRONLY);

	/*Seek for the boot block*/
	pos = lseek(fd, 1024, SEEK_SET);
	printf("Seek == %d \n", (int)pos);

	/*Create super block and allocate it 4K*/
	len = write(fd, &sb, sizeof(sb));
	printf("value check %d", pos);
	pos = lseek(fd, BLOCK_SIZE - len, SEEK_SET);
	printf("Seek == %d \n", (int)pos);

	/*Create a block bit map*/
	len = write(fd, &block_bitmap, sizeof(block_bitmap));
	pos = lseek(fd, BLOCK_SIZE, SEEK_SET);
	printf("Seek == %d \n", (int)pos);


	/*Create a inode bitmap*/
	len = write(fd, &inode_bitmap, sizeof(inode_bitmap));
	pos = lseek(fd, BLOCK_SIZE, SEEK_SET);
	printf("Seek == %d \n", (int)pos);


	return 0;
}
