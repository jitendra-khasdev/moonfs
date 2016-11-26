#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include "moonfs.h"


/*
 * In the mount basically we read disk data structure and fill the
 * in-memory data structure.
 *
 * In current we do not have any disk data structure, we are here
 * filing hardcoded values.
 */

static struct super_operations moomfs_super_ops = {



};

static struct file_operations moonfs_fops = {


};


static struct inode_operations moonfs_iops = {


};

static struct super_operations moonfs_super_ops = {

};


int moonfs_fill_super (struct super_block *sb, void *data, int temp)
{
	struct moonfs_sb_info *mn_sb;
	struct inode *moon_inode;

	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = 0xABC;
	sb->s_time_gran = 1;
	sb->s_op = &moonfs_super_ops;

	moon_inode = new_inode(sb);
	moon_inode->i_atime = moon_inode->i_mtime = moon_inode->i_ctime = CURRENT_TIME;
	inode_init_owner(moon_inode, S_IFDIR | 0755, 0);
	moon_inode->i_ino = get_next_ino();
	moon_inode->i_blocks = 0;

	moon_inode->i_op = &moonfs_iops;
	moon_inode->i_fop = &moonfs_fops;

	printk(KERN_INFO "Valid super read complete\n");

	return 0;
}


static struct dentry *moonfs_mount (struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	printk(KERN_INFO "Mount sys call is called\n");
	return mount_nodev(fs_type, flags, data, moonfs_fill_super);
}

static void moonfs_kill_sb (struct super_block *sb)
{
	printk(KERN_INFO "un mount sys call is called\n");
}

static struct file_system_type moonfs_type = {
	.name = "moonfs",
	.owner = THIS_MODULE,
	.mount = moonfs_mount,
	.kill_sb = moonfs_kill_sb,
};


static int moon_init(void)
{
	int err;
	printk("Welcome to moon fs\n");

	err = register_filesystem(&moonfs_type);

	if (err != 0)
		printk(KERN_INFO "Error in creating file system\n");
	return 0;
}

static void moon_exit(void)
{
	printk("Unregister moon file system\n");
}

module_init(moon_init);
module_exit(moon_exit);
