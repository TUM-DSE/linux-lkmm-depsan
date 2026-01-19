#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing LKMM primitives");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_PRIMITIVES
#define _DEPSAN_PRIMITIVES

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wunused-variable"
extern void foo(void);
extern void bar(void);

#define MAX1 1
#define MAX2 42

static int x = 0;
static int *X = &x;
static int V = 0;
static int W = 0;

static atomic_t at = ATOMIC_INIT(0);
static atomic_t *A = &at;

static int __rcu *R = &x;

static spinlock_t l = __SPIN_LOCK_UNLOCKED(l);
static spinlock_t *L = &l;

/*
 * From https://github.com/torvalds/linux/blob/master/tools/memory-model/linux-kernel.def
 */

// ONCE
noinline void ronce(void) {
	int r1 = READ_ONCE(x);
};
noinline void wonce(void) {
	WRITE_ONCE(x,V);
};

// Release Acquire and friends
noinline void smp_sr(void) {
	smp_store_release(X,V);
};
noinline void smp_la(void) {
	int r1 = smp_load_acquire(X);
};
noinline void rcu_asgn(void) {
	rcu_assign_pointer(R,V);
};
noinline void rcu_drf(void) {
	int *r1 = rcu_dereference(R);
};
noinline void smp_smb(void) {
	smp_store_mb(x,V);
};

// Fences
noinline void smp_full(void) {
	smp_mb();
};
noinline void smp_read(void) {
	smp_rmb();
};
noinline void smp_write(void) {
	smp_wmb();
};
noinline void smp_mb_ba(void) {
	smp_mb__before_atomic();
};
noinline void smp_mb_aa(void) {
	smp_mb__after_atomic();
};
noinline void smp_mb_asl(void) {
	smp_mb__after_spinlock();
};
noinline void smp_mb_aul(void) {
	smp_mb__after_unlock_lock();
};
noinline void smp_mb_arcu(void) {
	smp_mb__after_srcu_read_unlock();
};
noinline void comp_bar(void) {
	barrier();
};

// Exchange
noinline void ret_xchg(void) {
	int r1 = xchg(&x,V);
};
noinline void ret_xchg_rlx(void) {
	int r1 = xchg_relaxed(&x,V);
};
noinline void ret_xchg_rel(void) {
	int r1 = xchg_release(&x,V);
};
noinline void ret_xchg_acq(void) {
	int r1 = xchg_acquire(&x,V);
};
noinline void ret_cmpxchg(void) {
	int r1 = cmpxchg(&x,V,W);
};
noinline void ret_cmpxchg_rlx(void) {
	int r1 = cmpxchg_relaxed(&x,V,W);
};
noinline void ret_cmpxchg_acq(void) {
	int r1 = cmpxchg_acquire(&x,V,W);
};
noinline void ret_cmpxchg_rel(void) {
	int r1 = cmpxchg_release(&x,V,W);
};

// Spinlocks
noinline void s_lock(void) {
	spin_lock(L);
};
noinline void s_ulock(void) {
	spin_unlock(L);
};
noinline void s_tlock(void) {
	int r1 = spin_trylock(L);
};
noinline void s_ilock(void) {
	int r1 = spin_is_locked(L);
};

// RCU
noinline void rcu_enter(void) {
	rcu_read_lock();
};
noinline void rcu_exit(void) {
	rcu_read_unlock();
};
noinline void rcu_sync(void) {
	synchronize_rcu();
};
noinline void rcu_sync_e(void) {
	synchronize_rcu_expedited();
};

// SRCU
// srcu_read_lock(A);
// srcu_read_unlock(A,Y);
// srcu_down_read(A);
// srcu_up_read(A,Y);
// synchronize_srcu(A);
// synchronize_srcu_expedited(A);

// Atomic
noinline void at_ld(void) {
	int r1 = atomic_read(A);
};
noinline void at_st(void) {
	atomic_set(A,V);
};
noinline void at_lda(void) {
	int r1 = atomic_read_acquire(A);
};
noinline void at_str(void) {
	atomic_set_release(A,V);
};

noinline void at_add(void) {
	atomic_add(V,A);
};
noinline void at_sub(void) {
	atomic_sub(V,A);
};
noinline void at_and(void) {
	atomic_and(V,A);
};
noinline void at_or(void) {
	atomic_or(V,A);
};
noinline void at_xor(void) {
	atomic_xor(V,A);
};
noinline void at_inc(void) {
	atomic_inc(A);
};
noinline void at_dec(void) {
	atomic_dec(A);
};
noinline void at_andnot(void) {
	atomic_andnot(V,A);
};

noinline void at_add_ret(void) {
	int r1 = atomic_add_return(V,A);
};
noinline void at_add_ret_rlx(void) {
	int r1 = atomic_add_return_relaxed(V,A);
};
noinline void at_add_ret_acq(void) {
	int r1 = atomic_add_return_acquire(V,A);
};
noinline void at_add_ret_rel(void) {
	int r1 = atomic_add_return_release(V,A);
};
noinline void at_fetch_add(void) {
	int r1 = atomic_fetch_add(V,A);
};
noinline void at_fetch_add_rlx(void) {
	int r1 = atomic_fetch_add_relaxed(V,A);
};
noinline void at_fetch_add_acq(void) {
	int r1 = atomic_fetch_add_acquire(V,A);
};
noinline void at_fetch_add_rel(void) {
	int r1 = atomic_fetch_add_release(V,A);
};

noinline void at_fetch_and(void) {
	int r1 = atomic_fetch_and(V,A);
};
noinline void at_fetch_and_rlx(void) {
	int r1 = atomic_fetch_and_relaxed(V,A);
};
noinline void at_fetch_and_acq(void) {
	int r1 = atomic_fetch_and_acquire(V,A);
};
noinline void at_fetch_and_rel(void) {
	int r1 = atomic_fetch_and_release(V,A);
};

noinline void at_fetch_or(void) {
	int r1 = atomic_fetch_or(V,A);
};
noinline void at_fetch_or_rlx(void) {
	int r1 = atomic_fetch_or_relaxed(V,A);
};
noinline void at_fetch_or_acq(void) {
	int r1 = atomic_fetch_or_acquire(V,A);
};
noinline void at_fetch_or_rel(void) {
	int r1 = atomic_fetch_or_release(V,A);
};

noinline void at_fetch_xor(void) {
	int r1 = atomic_fetch_xor(V,A);
};
noinline void at_fetch_xor_rlx(void) {
	int r1 = atomic_fetch_xor_relaxed(V,A);
};
noinline void at_fetch_xor_acq(void) {
	int r1 = atomic_fetch_xor_acquire(V,A);
};
noinline void at_fetch_xor_rel(void) {
	int r1 = atomic_fetch_xor_release(V,A);
};

noinline void at_inc_ret(void) {
	int r1 = atomic_inc_return(A);
};
noinline void at_inc_ret_rlx(void) {
	int r1 = atomic_inc_return_relaxed(A);
};
noinline void at_inc_ret_acq(void) {
	int r1 = atomic_inc_return_acquire(A);
};
noinline void at_inc_ret_rel(void) {
	int r1 = atomic_inc_return_release(A);
};
noinline void at_fetch_inc(void) {
	int r1 = atomic_fetch_inc(A);
};
noinline void at_fetch_inc_rlx(void) {
	int r1 = atomic_fetch_inc_relaxed(A);
};
noinline void at_fetch_inc_acq(void) {
	int r1 = atomic_fetch_inc_acquire(A);
};
noinline void at_fetch_inc_rel(void) {
	int r1 = atomic_fetch_inc_release(A);
};

noinline void at_sub_ret(void) {
	int r1 = atomic_sub_return(V,A);
};
noinline void at_sub_ret_rlx(void) {
	int r1 = atomic_sub_return_relaxed(V,A);
};
noinline void at_sub_ret_acq(void) {
	int r1 = atomic_sub_return_acquire(V,A);
};
noinline void at_sub_ret_rel(void) {
	int r1 = atomic_sub_return_release(V,A);
};
noinline void at_fetch_sub(void) {
	int r1 = atomic_fetch_sub(V,A);
};
noinline void at_fetch_sub_rlx(void) {
	int r1 = atomic_fetch_sub_relaxed(V,A);
};
noinline void at_fetch_sub_acq(void) {
	int r1 = atomic_fetch_sub_acquire(V,A);
};
noinline void at_fetch_sub_rel(void) {
	int r1 = atomic_fetch_sub_release(V,A);
};

noinline void at_dec_ret(void) {
	int r1 = atomic_dec_return(A);
};
noinline void at_dec_ret_rlx(void) {
	int r1 = atomic_dec_return_relaxed(A);
};
noinline void at_dec_ret_acq(void) {
	int r1 = atomic_dec_return_acquire(A);
};
noinline void at_dec_ret_rel(void) {
	int r1 = atomic_dec_return_release(A);
};
noinline void at_fetch_dec(void) {
	int r1 = atomic_fetch_dec(A);
};
noinline void at_fetch_dec_rlx(void) {
	int r1 = atomic_fetch_dec_relaxed(A);
};
noinline void at_fetch_dec_acq(void) {
	int r1 = atomic_fetch_dec_acquire(A);
};
noinline void at_fetch_dec_rel(void) {
	int r1 = atomic_fetch_dec_release(A);
};

noinline void at_xchg(void) {
	int r1 = atomic_xchg(A,V);
};
noinline void at_xchg_rlx(void) {
	int r1 = atomic_xchg_relaxed(A,V);
};
noinline void at_xchg_rel(void) {
	int r1 = atomic_xchg_release(A,V);
};
noinline void at_xchg_acq(void) {
	int r1 = atomic_xchg_acquire(A,V);
};
noinline void at_cmpxchg(void) {
	int r1 = atomic_cmpxchg(A,V,W);
};
noinline void at_cmpxchg_rlx(void) {
	int r1 = atomic_cmpxchg_relaxed(A,V,W);
};
noinline void at_cmpxchg_acq(void) {
	int r1 = atomic_cmpxchg_acquire(A,V,W);
};
noinline void at_cmpxchg_rel(void) {
	int r1 = atomic_cmpxchg_release(A,V,W);
};

noinline void at_sub_and_test(void) {
	int r1 = atomic_sub_and_test(V,A);
};
noinline void at_dec_and_test(void) {
	int r1 = atomic_dec_and_test(A);
};
noinline void at_inc_and_test(void) {
	int r1 = atomic_inc_and_test(A);
};
noinline void at_add_negative(void) {
	int r1 = atomic_add_negative(V,A);
};
noinline void at_add_negative_rlx(void) {
	int r1 = atomic_add_negative_relaxed(V,A);
};
noinline void at_add_negative_acq(void) {
	int r1 = atomic_add_negative_acquire(V,A);
};
noinline void at_add_negative_rel(void) {
	int r1 = atomic_add_negative_release(V,A);
};

noinline void at_fetch_andnot(void) {
	int r1 = atomic_fetch_andnot(V,A);
};
noinline void at_fetch_andnot_rlx(void) {
	int r1 = atomic_fetch_andnot_relaxed(V,A);
};
noinline void at_fetch_andnot_acq(void) {
	int r1 = atomic_fetch_andnot_acquire(V,A);
};
noinline void at_fetch_andnot_rel(void) {
	int r1 = atomic_fetch_andnot_release(V,A);
};

noinline void at_add_unless(void) {
	int r1 = atomic_add_unless(A,V,W);
};

int all(void) {
	ronce();
	wonce();
	smp_sr();
	smp_la();
	rcu_asgn();
	rcu_drf();
	smp_smb();
	// Fences
	smp_full();
	smp_read();
	smp_write();
	smp_mb_ba();
	smp_mb_aa();
	smp_mb_asl();
	smp_mb_aul();
	smp_mb_arcu();
	comp_bar();
	// Exchange
	ret_xchg();
	ret_xchg_rlx();
	ret_xchg_rel();
	ret_xchg_acq();
	ret_cmpxchg();
	ret_cmpxchg_rlx();
	ret_cmpxchg_acq();
	ret_cmpxchg_rel();
	// Spinlocks
	s_lock();
	s_ulock();
	s_tlock();
	s_ilock();
	// RCU
	rcu_enter();
	rcu_exit();
	rcu_sync();
	rcu_sync_e();
	// Atomic
	at_ld();
	at_st();
	at_lda();
	at_str();
	at_add();
	at_sub();
	at_and();
	at_or();
	at_xor();
	at_inc();
	at_dec();
	at_andnot();
	at_add_ret();
	at_add_ret_rlx();
	at_add_ret_acq();
	at_add_ret_rel();
	at_fetch_add();
	at_fetch_add_rlx();
	at_fetch_add_acq();
	at_fetch_add_rel();
	at_fetch_and();
	at_fetch_and_rlx();
	at_fetch_and_acq();
	at_fetch_and_rel();
	at_fetch_or();
	at_fetch_and_rlx();
	at_fetch_and_acq();
	at_fetch_and_rel();
	at_fetch_xor();
	at_fetch_xor_rlx();
	at_fetch_xor_acq();
	at_fetch_xor_rel();
	at_inc_ret();
	at_inc_ret_rlx();
	at_inc_ret_acq();
	at_inc_ret_rel();
	at_fetch_inc();
	at_fetch_inc_rlx();
	at_fetch_inc_acq();
	at_fetch_inc_rel();
	at_sub_ret();
	at_sub_ret_rlx();
	at_sub_ret_acq();
	at_sub_ret_rel();
	at_fetch_sub();
	at_fetch_sub_rlx();
	at_fetch_sub_acq();
	at_fetch_sub_rel();
	at_dec_ret();
	at_dec_ret_rlx();
	at_dec_ret_acq();
	at_dec_ret_rel();
	at_fetch_dec();
	at_fetch_dec_rlx();
	at_fetch_dec_acq();
	at_fetch_dec_rel();
	at_xchg();
	at_xchg_rlx();
	at_xchg_rel();
	at_xchg_acq();
	at_cmpxchg();
	at_cmpxchg_rlx();
	at_cmpxchg_acq();
	at_cmpxchg_rel();
	at_sub_and_test();
	at_dec_and_test();
	at_inc_and_test();
	at_add_negative();
	at_add_negative_rlx();
	at_add_negative_acq();
	at_add_negative_rel();
	at_fetch_andnot();
	at_fetch_andnot_rlx();
	at_fetch_andnot_acq();
	at_fetch_andnot_rel();
	at_add_unless();

	return 0;
}

static int depsan_primitives_init(void)
{
	return all();
}

static void depsan_primitives_exit(void) {}
#pragma clang diagnostic pop

module_init(depsan_primitives_init);
module_exit(depsan_primitives_exit);

#endif /* _DEPSAN_PRIMITIVES */
