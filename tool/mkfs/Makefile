all:
	dd if=/dev/zero of=disk_mn_fs bs=1024 count=131072
	gcc -g -o mkfs moon_main.c moon_mkfs.c moon_mkfs.h
	gcc -g -o dump dump_mkfs.c
	mkdir -p mnt

clean:
	rm -rf mkfs dump disk_mn_fs mnt

