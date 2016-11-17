# Make file for moon super block micro scope
#

all: main.o
	gcc -o moon_sb main.o moon_types.h

disk:
	dd if=/dev/zero of=disk_mn_fs bs=1024 count=131072
	mkfs.ext2 disk_mn_fs

clean:
	rm -r moon_sb *.o disk_mn_fs
