#/bin/bash

FS_DIR=/root/moonfs
SRC_DIR=$FS_DIR/src
MKFS_DIR=$FS_DIR/tool/mkfs
LOOP_DEV=`losetup -f`

function install_fs()
{
	cd $SRC_DIR
	make all
	insmod moonfs.ko
}

function setup_disk()
{
	cd $MKFS_DIR
	make all
	echo "Setting up loop back devices $LOOP_DEV"
	losetup $LOOP_DEV disk_mn_fs
	./mkfs $LOOP_DEV
	mount -t moonfs $LOOP_DEV mnt
}

function remove_disk()
{
	cd $MKFS_DIR
	umount mnt
	losetup -d /dev/loop0
	make clean
}

function uninstall_fs()
{
	cd $SRC_DIR
	rmmod moonfs
	make clean
}

if [ $1 == 1 ]; then
	install_fs
	setup_disk
fi

if [ $1 == 0 ]; then
	remove_disk
	uninstall_fs
fi
