#include <stdio.h>
#include "moon_mkfs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

	int fd, pos, bytes;
	struct super_block sb;

	if (argc != 2) {
		printf("Arguments Missing!");
		return -1;
	}

	fd  = open(argv[1], O_RDWR | O_CREAT, 755);

	pos = lseek(fd, BOOT_BLOCK, SEEK_SET);

	bytes = read(fd, &sb, sizeof(sb));

	printf("Super Block Info");
	printf("Name == %s\n", sb.name);
	printf("Name == %d\n", sb.size);
	printf("Name == %d\n", sb.block_count);
	return 0;
}
