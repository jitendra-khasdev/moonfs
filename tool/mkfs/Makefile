all:
	dd if=/dev/zero of=disk_mn_fs bs=1024 count=131072

build:
	gcc -g -o mkfs moon_main.c moon_mkfs.c moon_mkfs.h

clean:
	rm mkfs disk_mn_fs

