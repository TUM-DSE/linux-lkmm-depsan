#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing ctrl dependency litmus tests");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_CTRL_TEST
#define _DEPSAN_CTRL_TEST

extern void foo(void);
extern void bar(void);

#define MAX1 1
#define MAX2 42

static int x = 0;
static int y = 0;
static int z = 0;

static int shared[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// See memory-barriers.txt

static noinline void bug_ronce_ronce(void) {
	int r1 = READ_ONCE(x);
        if (r1) {
                /* BUG: No address dependency!!! */
                int r2 = READ_ONCE(y);
        }
}

static noinline void ronce_wonce(void) {
	int r1 = READ_ONCE(x);
	if (r1) {
		WRITE_ONCE(y, 1);
	}
}

static noinline void bug_ronce_woncewonce(void) {
	int r1 = READ_ONCE(x);
        if (r1) {
                barrier();
                WRITE_ONCE(y, 1);
		foo();
        } else {
                barrier();
                WRITE_ONCE(y, 1);
		bar();
        }
}

static noinline void ronce_woncewonce(void) {
	int r1 = READ_ONCE(x);
        if (r1) {
                WRITE_ONCE(y, 1);
		foo();
        } else {
                WRITE_ONCE(y, 2);
		bar();
        }
}

static noinline void bug_ronce_woncewonce_mod(void) {
	int r1 = READ_ONCE(x);
	if (r1 % MAX1) {
		WRITE_ONCE(y, 1);
		foo();
	} else {
		WRITE_ONCE(y, 2);
		bar();
	}
}

static noinline void ronce_woncewonce_mod(void) {
	int r1 = READ_ONCE(x);
	if (r1 % MAX2) {
		WRITE_ONCE(y, 1);
		foo();
	} else {
		WRITE_ONCE(y, 2);
		bar();
	}
}

static noinline void bug_ronce_wonce_shorted(void) {
	int r1 = READ_ONCE(x);
	if (r1 || 1 > 0) {
		WRITE_ONCE(y, 1);
	}
}

static noinline void overapprox_ronce_woncewonce_wonce(void) {
	int r1 = READ_ONCE(x);
	if (r1) {
		WRITE_ONCE(y, 1);
	} else {
		WRITE_ONCE(y, 2);
	}
	WRITE_ONCE(z, 3);
}

int all_ctrl_tests(void)
{
	bug_ronce_ronce();
	ronce_wonce();
	bug_ronce_woncewonce();
	ronce_woncewonce();
	bug_ronce_woncewonce_mod();
	ronce_woncewonce_mod();
	bug_ronce_wonce_shorted();
	overapprox_ronce_woncewonce_wonce();

	return 0;
}

static int depsan_ctrl_init(void)
{
	return all_ctrl_tests();
}

static void depsan_ctrl_exit(void) {}

module_init(depsan_ctrl_init);
module_exit(depsan_ctrl_exit);

#endif /* _DEPSAN_CTRL_TEST */
