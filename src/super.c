#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/slab.h>
#include "moonfs.h"

#define MOONFS_MAGIC     0x73616d70 /* "SAMP" */
/*
 * In the mount basically we read disk data structure and fill the
 * in-memory data structure.
 *
 * In current we do not have any disk data structure, we are here
 * filing hardcoded values.
 */

static void moon_put_super(struct super_block *sb)                          
{                                                                               
	struct moon_sb_info *sfs_sb;                                        

	sfs_sb = SFS_SB(sb);                                                    

	if (sfs_sb == NULL) {                                                   
		/* Empty superblock info
		 * passed to unmount */                   
		return;                                                         
	}                                                                       

	/* FS-FILLIN your fs specific umount
	 * logic here */                      
	kfree(sfs_sb);                                                          
	sb->s_fs_info = NULL;                                                   
} 




static struct super_operations moonfs_super_ops = {
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.put_super      = moon_put_super,
};

struct inode *moon_get_inode(struct super_block *sb, const struct inode *dir, 
			      int mode, dev_t dev)
{
	
	struct inode *inode = new_inode(sb);
	
	if (inode) {
		inode->i_ino = get_next_ino();
		inode_init_owner(inode, dir, mode);
		inode->i_blocks = 0;
		inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
		switch (mode & S_IFMT) {
			default:
				init_special_inode(inode, mode, dev);
				break;
			case S_IFREG:
				printk("File inode \n");
				inode->i_op = &simple_dir_inode_operations;
				break;

			case S_IFDIR:
				printk("Dir inode\n");
				inode->i_op = &simple_dir_inode_operations;
				inode_inc_link_count(inode);
				break;
		}
	}
	return inode;
}



int moonfs_fill_super (struct super_block *sb, void *data, int temp)
{
	struct moon_sb_info *msbi;
	struct inode *root;	
	struct moon_super_block *msb;
	unsigned int err;
	struct buffer_head *bh = NULL;

	err = -ENOMEM;
	msbi = kzalloc(sizeof(struct moon_sb_info), GFP_KERNEL);
	if (!msbi) {
		kfree(msbi);
		goto fail;
	}

	sb->s_fs_info = msbi;

	bh = sb_bread(sb, 1024);
	if (!bh) {
		brelse(bh);
		printk("Unable to read superblock");
		goto fail;
	}

	msb = (struct moon_super_block *)(char *)bh->b_data;
	
	if (msb) {
		printk("Disk Super Block\n");
		printk("name == %s\n", msb->name);
	}

	sb->s_maxbytes = MAX_LFS_FILESIZE; /* NB: may be too large for mem */
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = MOONFS_MAGIC;
	sb->s_op = &moonfs_super_ops;
	sb->s_time_gran = 1; /* 1 nanosecond time granularity */

	root = moon_get_inode(sb, NULL, S_IFDIR | 0755, 0);
	if (!root)
		goto fail;
	
	sb->s_root = d_make_root(root);
	if (!sb->s_root) {
		iput(root);
		printk("Unable to read root inode\n");
		goto fail;
	}
	printk("Mount function getting called\n");	
	
	return 0;

fail:
	return err;
}


static struct dentry *moonfs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	return mount_bdev(fs_type, flags, dev_name, data, moonfs_fill_super);

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
