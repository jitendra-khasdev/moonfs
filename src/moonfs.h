/*
 * Nov-2016
 * File Name : src/moonfs.h
 * Description : This file contains in-memory data structure and disk data 
 * structure for the
 * moonfs.
 *
 */
#define MOON_BLOCK_SIZE 4096

/* 
 * moonfs_sb_info is in memory data structure to perform operation in fs.
 */

struct moon_sb_info {
	char name[20];
	int val;
	int num;
};

/*
 * moon_super_block is disk data structure.
 */
struct moon_super_block {                                                       
	char name[10];                                                          
	int size;                                                               
	int block_count;                                                        
};                                                                              
                                                                                
                                                                                
struct moon_inode {                                                             
	int blocks;                                                             
	int ptr[10];                                                            
}; 


static inline struct moon_sb_info *                                         
SFS_SB(struct super_block *sb)                                                  
{                                                                               
	        return sb->s_fs_info;                                                   
}


