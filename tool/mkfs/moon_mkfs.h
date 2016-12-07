
#define BLOCK_SIZE 4096
#define BOOT_BLOCK 1024

struct super_block {
	char name[10];
	int size;
	int block_count;
};


struct inode {
	int blocks;
	int ptr[10];
};

char block_bitmap[BLOCK_SIZE];
char inode_bitmap[BLOCK_SIZE];
int make_boot(int , int);
int cal_block(int);
int make_sb(int);
int make_block_bitmap(int, char *);
int make_inode_bitmap(int, char *);
int cal_inode_tblock(int, long int);
int make_inode_table(int, int);
int make_data_blocks(int, int);
