#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing address dependency litmus tests");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_ADDR_TEST
#define _DEPSAN_ADDR_TEST

static int x = 0;
static int y = 0;
static int z = 0;

static int shared[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static noinline void ronce_ronce(void)
{
	int r1;
	int *r2;
	int r3;

	r1 = READ_ONCE(x);

	r2 = &shared[r1];

	r3 = READ_ONCE(*r2);
}

int all_addr_tests(void)
{

	ronce_ronce();
	return 0;
}

static int depsan_addr_init(void)
{
	return all_addr_tests();
}

static void depsan_addr_exit(void) {}

module_init(depsan_addr_init);
module_exit(depsan_addr_exit);

#endif /* _DEPSAN_TEST */
