#include <linux/fs.h>
#include "moonfs.h"
extern struct inode *moon_get_inode(struct super_block *sb, const struct inode 
				*dir, int mode, dev_t dev);

int moon_symlink (struct inode *dir, struct dentry *dentry, const char *symname)
{
	struct inode *inode;
	int len, err = -ENOSPC;

	inode = moon_get_inode (dir->i_sb, dir, S_IFLNK|S_IRWXUGO, 0);
	if (inode) {
		len = strlen(symname) + 1;
		err = page_symlink(inode, symname, len);

		if (!err) {
			if (dir->i_mode & S_ISGID)
				inode->i_gid = dir->i_gid;
			d_instantiate(dentry, dir);
			dget(dentry);
			dir->i_mtime = dir->i_ctime = CURRENT_TIME;
		} else
			iput(inode);
	}
	return err;
}

int moon_mknod (struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
{
	struct inode *inode = moon_get_inode(dir->i_sb, dir, mode, dev);
	int err = -ENOSPC;

	if (inode) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode)) {
			inode->i_mode |= S_ISGID; 
		}
		d_instantiate(dentry, inode);
		dget(dentry);
		err = 0;
		dir->i_mtime = dir->i_ctime = CURRENT_TIME;
		dir->i_size +=  0x40;
	}
	return err;
}

int moon_mkdir (struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int ret;

	ret = 0;

	ret = moon_mknod(dir, dentry, mode | S_IFDIR, 0);

	if (!ret) {
		inode_inc_link_count(dir);
	}
	return ret;
}


int moon_create (struct inode *dir, struct dentry *dentry, umode_t mode, bool excl)
{
	return moon_mknod (dir, dentry, mode | S_IFREG, 0);
}

struct inode_operations moon_file_inode_ops = {
	.getattr = simple_getattr,
};

struct inode_operations moon_dir_inode_ops = {
	.lookup		= simple_lookup, 
	.create		= moon_create,
	.link		= simple_link,
	.unlink		= simple_unlink,
	.symlink	= moon_symlink,
	.mkdir		= moon_mkdir,
	.rmdir		= simple_rmdir,
	.mknod		= moon_mknod,
	.rename		= simple_rename,
};
