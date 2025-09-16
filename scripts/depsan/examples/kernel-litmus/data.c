#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing data dependency litmus tests");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_DATA_TEST
#define _DEPSAN_DATA_TEST

static int x = 0;
static int y = 0;
static int z = 0;

static int shared[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

int all_data_tests(void)
{

	return 0;
}

static int depsan_data_init(void)
{
	return all_data_tests();
}

static void depsan_data_exit(void) {}

module_init(depsan_data_init);
module_exit(depsan_data_exit);

#endif /* _DEPSAN_DATA_TEST */
