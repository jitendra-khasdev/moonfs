#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "moon_types.h"

struct ext2_super_block {
	__u32		s_inodes_count;
	__u32		s_blocks_count;
	__u32		s_r_blocks_count;
	__u32		s_free_blocks_count;
	__u32		s_free_inodes_count;
	__u32		s_first_data_block;
	__u32		s_log_block_size;
	__u32		s_dummy3[7];
	unsigned char	s_magic[2];
	__u16		s_state;
	__u32		s_dummy5[8];
	__u32		s_feature_compat;
	__u32		s_feature_incompat;
	__u32		s_feature_ro_compat;
	unsigned char   s_uuid[16];
	char	   s_volume_name[16];
	char	s_last_mounted[64];
	__u32	s_algorithm_usage_bitmap;
	__u8	s_prealloc_blocks;
	__u8	s_prealloc_dir_blocks;
	__u16	s_reserved_gdt_blocks;
	__u8	s_journal_uuid[16];
	__u32	s_journal_inum;
	__u32	s_journal_dev;
	__u32	s_last_orphan;
	__u32	s_hash_seed[4];
	__u8	s_def_hash_version;
	__u8	s_jnl_backup_type;
	__u16	s_reserved_word_pad;
	__u32	s_default_mount_opts;
	__u32	s_first_meta_bg;
	__u32	s_mkfs_time;
	__u32	s_jnl_blocks[17];
	__u32	s_blocks_count_hi;
	__u32	s_r_blocks_count_hi;
	__u32	s_free_blocks_hi;
	__u16	s_min_extra_isize;
	__u16	s_want_extra_isize;
	__u32	s_flags;
	__u16   s_raid_stride;
	__u16   s_mmp_interval;
	__u64   s_mmp_block;
	__u32   s_raid_stripe_width;
	__u32   s_reserved[163];
};

int main(int argc, char *argv[])
{
	int fd, i;
	struct ext2_super_block super_block;

	if (argc != 2) {
		printf("argument missing:\n eg. moon_sb <disk/filename>\n");
		exit(0);
	}

	fd = open(argv[1], O_RDONLY);

	lseek(fd, 1024, SEEK_SET);

	read(fd, &super_block, sizeof(struct ext2_super_block));

	printf("Magic Number == 0x%X%X\n", (unsigned int)super_block.s_magic[1], (unsigned int)super_block.s_magic[0]);

	printf("UUID == ");
	for (i = 0; i < 16; i++) {
		printf("%x", (unsigned int)super_block.s_uuid[i]);
	}

	printf("\n");
	printf("Super_block_count == %d \n", super_block.s_blocks_count);
	printf("Super_r_blocks_count == %d \n", super_block.s_r_blocks_count);
	printf("Super_free_blocks_count == %d \n", super_block.s_free_blocks_count);
	printf("Super_first_data_block == %d \n", super_block.s_first_data_block);
	printf("Super_log_block_size == %d \n", super_block.s_log_block_size);
	printf("Super_state == %d \n", super_block.s_state);
	printf("Super_feature_compat == %d \n", super_block.s_feature_compat);
	printf("Super_feature_incompat == %d \n", super_block.s_feature_incompat);
	printf("Super_feature_ro_compat == %d \n", super_block.s_feature_ro_compat);
	printf("Super_algorithm_usage_bitmap == %d \n", super_block.s_algorithm_usage_bitmap);
	printf("Super_prealloc_blocks== %d \n", super_block.s_prealloc_blocks);
	printf("Super_prealloc_dir_blocks== %d \n", super_block.s_prealloc_dir_blocks);
	printf("Super_reserved_gdt_blocks== %d \n", super_block.s_reserved_gdt_blocks);
	printf("Super_journal_inum== %d \n", super_block.s_journal_inum);
	printf("Super_journal_dev== %d \n", super_block.s_journal_dev);
	printf("Super_last_orphan== %d \n", super_block.s_last_orphan);
	printf("Super_last_orphan== %d \n", super_block.s_last_orphan);
	printf("Super_def_hash_version== %d \n", super_block.s_def_hash_version);
	printf("Super_jnl_backup_type== %d \n", super_block.s_jnl_backup_type);
	printf("Super_reserved_word_pad== %d \n", super_block.s_reserved_word_pad);
	printf("Super_default_mount_opts== %d \n", super_block.s_default_mount_opts);
	printf("Super_first_meta_bg== %d \n", super_block.s_first_meta_bg);
	printf("Super_mkfs_time== %d \n", super_block.s_mkfs_time);
	printf("Super_blocks_count_hi== %d \n", super_block.s_blocks_count_hi);
	printf("Super_r_blocks_count_hi== %d \n", super_block.s_r_blocks_count_hi);
	printf("Super_free_blocks_hi== %d \n", super_block.s_free_blocks_hi);
	printf("Super_min_extra_isize== %d \n", super_block.s_min_extra_isize);
	printf("Super_want_extra_isize== %d \n", super_block.s_want_extra_isize);
	printf("Super_flags== %d \n", super_block.s_flags);
	printf("Super_raid_stride== %d \n", super_block.s_raid_stride);
	printf("Super_mmp_interval== %d \n", super_block.s_mmp_interval);
	printf("Super_mmp_block== %lld \n", super_block.s_mmp_block);
	printf("Super_raid_stripe_width== %d \n", super_block.s_raid_stripe_width);

	return 0;
}
