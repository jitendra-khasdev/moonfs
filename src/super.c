#include <linux/module.h>
#include <linux/init.h>


static int moon_init(void)
{
	printk("Welcome to moon fs\n");
	return 0;
}

static void moon_exit(void)
{
	printk("Unregister moon file system\n");
}

module_init(moon_init);
module_exit(moon_exit);
