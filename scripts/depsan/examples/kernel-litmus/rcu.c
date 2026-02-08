#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing rcu litmus tests");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_RCU_TEST
#define _DEPSAN_RCU_TEST

extern void foo(void);
extern void bar(void);

#define MAX1 1
#define MAX2 42

static int x = 0;
static int y = 0;
static int z = 0;
static atomic_t a1 = ATOMIC_INIT(0);
static int __rcu *x0 = &x;
static int __rcu *x1 = &y;

static int shared[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };


// See litmus auto/C-RW-Rs+RW-RCD
// Result: Never
// {
// 	x1=y0;
// }

static noinline void nodep(void) {
	int *r3=&z;

	rcu_read_lock();
	intptr_t r1 = READ_ONCE(*x0);
	rcu_assign_pointer(x1, r3);
	rcu_read_unlock();
}


static noinline void deref_cwonce(void) {
	int *r4=&y;

	rcu_read_lock();
	int *r1 = rcu_dereference(x1);
	// r4 = (r1 != r4);
	if (r1 != r4) {
		WRITE_ONCE(*r1, 1);
	}
	rcu_read_unlock();
}

// exists
// (0:r1=1 /\ 1:r1=x0)

// See rcu_dereference.txt
static noinline void bug_deref_aronce(void) {
	int local = 42;
	int *r3 = &local;

	rcu_read_lock();
	int *r1 = rcu_dereference(x0);
	if (r1 == r3) {
		int r2 = READ_ONCE(*r1); // can swap with r3
	}
	rcu_read_unlock();
}

static noinline void deref_aronce(void) {
	rcu_read_lock();
	int *r1 = rcu_dereference(x0);
	if (r1 == x1) {
		int r2 = READ_ONCE(*r1); // doesn't swap with x1, since it's global
	}
	rcu_read_unlock();
}

int all_rcu_tests(void)
{
	nodep();
	deref_cwonce();
	bug_deref_aronce();
	deref_aronce();
	return 0;
}

static int depsan_rcu_init(void)
{
	return all_rcu_tests();
}

static void depsan_rcu_exit(void) {}

module_init(depsan_rcu_init);
module_exit(depsan_rcu_exit);

#endif /* _DEPSAN_RCU_TEST */
