/*
 * Nov-2016
 * File Name : src/moonfs.h
 * Description : This file contains in-memory data structure and disk data 
 * structure for the
 * moonfs.
 *
 */


/* 
 * moonfs_sb_info is in memory data structure to perform operation in fs.
 */

struct moonfs_sb_info {
	char name[20];
	int val;
	int num;
};
