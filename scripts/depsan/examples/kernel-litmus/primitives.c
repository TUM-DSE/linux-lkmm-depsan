#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing LKMM primitives");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_PRIMITIVES
#define _DEPSAN_PRIMITIVES

extern void foo(void);
extern void bar(void);

#define MAX1 1
#define MAX2 42

static int x = 0;
static int y = 0;
static int z = 0;

static int shared[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

noinline void ronce(void) {
	int r1 = READ_ONCE(x);
};

noinline void wonce(void) {
	WRITE_ONCE(x, 1);
};

noinline void smp_lda(void) {
	int r1 = smp_load_acquire(&x);
};

noinline void smp_str(void) {
	smp_store_release(&x, 1);
};

noinline void smp_w_mb(void) {
	smp_wmb();
};

noinline void smp_r_mb(void) {
	smp_rmb();
};

noinline void smp_full(void) {
	smp_mb();
};

noinline void xchg_rlx(void) {
	int r1 = xchg_relaxed(&x, 1);
};
noinline void xchg_acq(void) {
	int r1 = xchg_acquire(&x, 1);
};
noinline void xchg_rel(void) {
	int r1 = xchg_release(&x, 1);
};
noinline void xchg_plain(void) {
	int r1 = xchg(&x, 1);
};

int all(void) {
	ronce();
	wonce();
	smp_lda();
	smp_str();
	smp_w_mb();
	smp_r_mb();
	smp_full();
	xchg_rlx();
	xchg_acq();
	xchg_rel();
	xchg_plain();

	return 0;
}

static int depsan_primitives_init(void)
{
	return all();
}

static void depsan_primitives_exit(void) {}

module_init(depsan_primitives_init);
module_exit(depsan_primitives_exit);

#endif /* _DEPSAN_PRIMITIVES */
