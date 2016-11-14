#include <linux/init.h>


static int moon_init(void)
{
	printk("Welcome to moon fs\n");
	return 0;
}

static void moon_exit()
{
	printk("Unregister moon file system\n");
}
