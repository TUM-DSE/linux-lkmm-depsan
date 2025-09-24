#include <linux/atomic.h>
#include <linux/types.h>
#include <asm-generic/barrier.h>

int x;
int y;

void ronce() {
	int r1 = READ_ONCE(x);
};

void wonce() {
	WRITE_ONCE(x, 1);
};

void smp_lda() {
	int r1 = smp_load_acquire(&x);
};

void smp_sta() {
	smp_store_release(&x, 1);
};

void smp_w_mb() {
	smp_wmb();
};

void smp_r_mb() {
	smp_rmb();
};

void smp_full() {
	smp_mb();
};

void xchg_rlx() {
	int r1 = xchg_relaxed(&x, 1);
};
void xchg_acq() {
	int r1 = xchg_acquire(&x, 1);
};
void xchg_rel() {
	int r1 = xchg_release(&x, 1);
};
void xchg_plain() {
	int r1 = xchg(&x, 1);
};

int main(void) {
	return 0;
};
