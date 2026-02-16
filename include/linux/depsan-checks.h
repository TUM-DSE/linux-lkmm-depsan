/* SPDX-License-Identifier: GPL-2.0 */
/*
 */

#ifndef _LINUX_DEPSAN_CHECKS_H
#define _LINUX_DEPSAN_CHECKS_H

/* Note: Only include what is already included by compiler.h. */
#include <linux/compiler_attributes.h>
#include <linux/types.h>

#ifndef __clang__
#define __builtin_annotation(e, m) e
#endif

static inline void __depsan_mb_b(void)			{ }
static inline void __depsan_mb_e(void)			{ }
static inline void __depsan_mb_ba_b(void)		{ }
static inline void __depsan_mb_ba_e(void)		{ }
static inline void __depsan_mb_aa_b(void)		{ }
static inline void __depsan_mb_aa_e(void)		{ }
static inline void __depsan_wmb_b(void)			{ }
static inline void __depsan_wmb_e(void)			{ }
static inline void __depsan_rmb_b(void)			{ }
static inline void __depsan_rmb_e(void)			{ }
static inline void __depsan_s_release_b(void)		{ }
static inline void __depsan_s_release_e(void)		{ }
static inline void __depsan_l_acquire_b(void)		{ }
static inline void __depsan_l_acquire_e(void)		{ }
static inline void __depsan_atomic_b(void)		{ }
static inline void __depsan_atomic_e(void)		{ }
static inline void __depsan_ronce_b(void)		{ }
static inline void __depsan_ronce_e(void)		{ }
static inline void __depsan_wonce_b(void)		{ }
static inline void __depsan_wonce_e(void)		{ }
static inline void __depsan_lock_b(void)		{ }
static inline void __depsan_lock_e(void)		{ }
static inline void __depsan_unlock_b(void)		{ }
static inline void __depsan_unlock_e(void)		{ }

static inline void __depsan_barrier_b(void)		{ }
static inline void __depsan_barrier_e(void)		{ }

static inline void __depsan_rcu_deref_b(void)		{ }
static inline void __depsan_rcu_deref_e(void)		{ }
static inline void __depsan_rcu_assign_b(void)		{ }
static inline void __depsan_rcu_assign_e(void)		{ }
static inline void __depsan_rcu_sync_b(void)		{ }
static inline void __depsan_rcu_sync_e(void)		{ }

/** Begin **/
/* Basic operations */
static inline void __depsan_atomic_read_b(void) { }
static inline void __depsan_atomic_set_b(void) { }
static inline void __depsan_atomic_read_acquire_b(void) { }
static inline void __depsan_atomic_set_release_b(void) { }

static inline void __depsan_atomic_long_read_b(void) { }
static inline void __depsan_atomic_long_set_b(void) { }
static inline void __depsan_atomic_long_read_acquire_b(void) { }
static inline void __depsan_atomic_long_set_release_b(void) { }

/* Non-value-returning atomics */
static inline void __depsan_atomic_add_b(void) { }
static inline void __depsan_atomic_sub_b(void) { }
static inline void __depsan_atomic_inc_b(void) { }
static inline void __depsan_atomic_dec_b(void) { }
static inline void __depsan_atomic_and_b(void) { }
static inline void __depsan_atomic_andnot_b(void) { }
static inline void __depsan_atomic_or_b(void) { }

static inline void __depsan_atomic_long_add_b(void) { }
static inline void __depsan_atomic_long_sub_b(void) { }
static inline void __depsan_atomic_long_inc_b(void) { }
static inline void __depsan_atomic_long_dec_b(void) { }
static inline void __depsan_atomic_long_and_b(void) { }
static inline void __depsan_atomic_long_andnot_b(void) { }
static inline void __depsan_atomic_long_or_b(void) { }

/* Value-returning atomics */

static inline void __depsan_atomic_fetch_add_b(void) { }
static inline void __depsan_atomic_xadd_b(void) { }
static inline void __depsan_atomic_fetch_add_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_add_acquire_b(void) { }
static inline void __depsan_atomic_fetch_add_release_b(void) { }

static inline void __depsan_atomic_long_fetch_add_b(void) { }
static inline void __depsan_atomic_long_fetch_add_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_add_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_add_release_b(void) { }

static inline void __depsan_atomic_fetch_inc_b(void) { }
static inline void __depsan_atomic_fetch_inc_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_inc_acquire_b(void) { }
static inline void __depsan_atomic_fetch_inc_release_b(void) { }

static inline void __depsan_atomic_long_fetch_inc_b(void) { }
static inline void __depsan_atomic_long_fetch_inc_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_inc_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_inc_release_b(void) { }

static inline void __depsan_atomic_fetch_sub_b(void) { }
static inline void __depsan_atomic_fetch_sub_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_sub_acquire_b(void) { }
static inline void __depsan_atomic_fetch_sub_release_b(void) { }

static inline void __depsan_atomic_long_fetch_sub_b(void) { }
static inline void __depsan_atomic_long_fetch_sub_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_sub_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_sub_release_b(void) { }

static inline void __depsan_atomic_fetch_dec_b(void) { }
static inline void __depsan_atomic_fetch_dec_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_dec_acquire_b(void) { }
static inline void __depsan_atomic_fetch_dec_release_b(void) { }

static inline void __depsan_atomic_long_fetch_dec_b(void) { }
static inline void __depsan_atomic_long_fetch_dec_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_dec_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_dec_release_b(void) { }

static inline void __depsan_atomic_fetch_and_b(void) { }
static inline void __depsan_atomic_fetch_and_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_and_acquire_b(void) { }
static inline void __depsan_atomic_fetch_and_release_b(void) { }

static inline void __depsan_atomic_long_fetch_and_b(void) { }
static inline void __depsan_atomic_long_fetch_and_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_and_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_and_release_b(void) { }

static inline void __depsan_atomic_fetch_andnot_b(void) { }
static inline void __depsan_atomic_fetch_andnot_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_andnot_acquire_b(void) { }
static inline void __depsan_atomic_fetch_andnot_release_b(void) { }

static inline void __depsan_atomic_long_fetch_andnot_b(void) { }
static inline void __depsan_atomic_long_fetch_andnot_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_andnot_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_andnot_release_b(void) { }

static inline void __depsan_atomic_fetch_or_b(void) { }
static inline void __depsan_atomic_fetch_or_relaxed_b(void) { }
static inline void __depsan_atomic_fetch_or_acquire_b(void) { }
static inline void __depsan_atomic_fetch_or_release_b(void) { }

static inline void __depsan_atomic_long_fetch_or_b(void) { }
static inline void __depsan_atomic_long_fetch_or_relaxed_b(void) { }
static inline void __depsan_atomic_long_fetch_or_acquire_b(void) { }
static inline void __depsan_atomic_long_fetch_or_release_b(void) { }

static inline void __depsan_atomic_add_return_b(void) { }
static inline void __depsan_atomic_add_return_relaxed_b(void) { }
static inline void __depsan_atomic_add_return_acquire_b(void) { }
static inline void __depsan_atomic_add_return_release_b(void) { }

static inline void __depsan_atomic_inc_return_b(void) { }
static inline void __depsan_atomic_inc_return_relaxed_b(void) { }
static inline void __depsan_atomic_inc_return_acquire_b(void) { }
static inline void __depsan_atomic_inc_return_release_b(void) { }

static inline void __depsan_atomic_long_inc_return_b(void) { }
static inline void __depsan_atomic_long_inc_return_relaxed_b(void) { }
static inline void __depsan_atomic_long_inc_return_acquire_b(void) { }
static inline void __depsan_atomic_long_inc_return_release_b(void) { }

static inline void __depsan_atomic_sub_return_b(void) { }
static inline void __depsan_atomic_sub_return_relaxed_b(void) { }
static inline void __depsan_atomic_sub_return_acquire_b(void) { }
static inline void __depsan_atomic_sub_return_release_b(void) { }

static inline void __depsan_atomic_long_sub_return_b(void) { }
static inline void __depsan_atomic_long_sub_return_relaxed_b(void) { }
static inline void __depsan_atomic_long_sub_return_acquire_b(void) { }
static inline void __depsan_atomic_long_sub_return_release_b(void) { }

static inline void __depsan_atomic_dec_return_b(void) { }
static inline void __depsan_atomic_dec_return_relaxed_b(void) { }
static inline void __depsan_atomic_dec_return_acquire_b(void) { }
static inline void __depsan_atomic_dec_return_release_b(void) { }

static inline void __depsan_atomic_long_dec_return_b(void) { }
static inline void __depsan_atomic_long_dec_return_relaxed_b(void) { }
static inline void __depsan_atomic_long_dec_return_acquire_b(void) { }
static inline void __depsan_atomic_long_dec_return_release_b(void) { }

static inline void __depsan_atomic_xchg_b(void) { }
static inline void __depsan_atomic_xchg_relaxed_b(void) { }
static inline void __depsan_atomic_xchg_release_b(void) { }
static inline void __depsan_atomic_xchg_acquire_b(void) { }

static inline void __depsan_atomic_long_xchg_b(void) { }
static inline void __depsan_atomic_long_xchg_relaxed_b(void) { }
static inline void __depsan_atomic_long_xchg_release_b(void) { }
static inline void __depsan_atomic_long_xchg_acquire_b(void) { }

static inline void __depsan_atomic_cmpxchg_b(void) { }
static inline void __depsan_atomic_cmpxchg_relaxed_b(void) { }
static inline void __depsan_atomic_cmpxchg_acquire_b(void) { }
static inline void __depsan_atomic_cmpxchg_release_b(void) { }

static inline void __depsan_atomic_long_cmpxchg_b(void) { }
static inline void __depsan_atomic_long_cmpxchg_relaxed_b(void) { }
static inline void __depsan_atomic_long_cmpxchg_acquire_b(void) { }
static inline void __depsan_atomic_long_cmpxchg_release_b(void) { }

static inline void __depsan_atomic_sub_and_test_b(void) { }
static inline void __depsan_atomic_dec_and_test_b(void) { }
static inline void __depsan_atomic_inc_and_test_b(void) { }
static inline void __depsan_atomic_add_negative_b(void) { }

static inline void __depsan_atomic_long_sub_and_test_b(void) { }
static inline void __depsan_atomic_long_dec_and_test_b(void) { }
static inline void __depsan_atomic_long_inc_and_test_b(void) { }
static inline void __depsan_atomic_long_add_negative_b(void) { }

/** End **/
/* Basic operations */
static inline void __depsan_atomic_read_e(void) { }
static inline void __depsan_atomic_set_e(void) { }
static inline void __depsan_atomic_read_acquire_e(void) { }
static inline void __depsan_atomic_set_release_e(void) { }

static inline void __depsan_atomic_long_read_e(void) { }
static inline void __depsan_atomic_long_set_e(void) { }
static inline void __depsan_atomic_long_read_acquire_e(void) { }
static inline void __depsan_atomic_long_set_release_e(void) { }

/* Non-value-returning atomics */
static inline void __depsan_atomic_add_e(void) { }
static inline void __depsan_atomic_sub_e(void) { }
static inline void __depsan_atomic_inc_e(void) { }
static inline void __depsan_atomic_dec_e(void) { }
static inline void __depsan_atomic_and_e(void) { }
static inline void __depsan_atomic_andnot_e(void) { }
static inline void __depsan_atomic_or_e(void) { }

static inline void __depsan_atomic_long_add_e(void) { }
static inline void __depsan_atomic_long_sub_e(void) { }
static inline void __depsan_atomic_long_inc_e(void) { }
static inline void __depsan_atomic_long_dec_e(void) { }
static inline void __depsan_atomic_long_and_e(void) { }
static inline void __depsan_atomic_long_andnot_e(void) { }
static inline void __depsan_atomic_long_or_e(void) { }

/* Value-returning atomics */

static inline void __depsan_atomic_fetch_add_e(void) { }
static inline void __depsan_atomic_xadd_e(void) { }
static inline void __depsan_atomic_fetch_add_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_add_acquire_e(void) { }
static inline void __depsan_atomic_fetch_add_release_e(void) { }

static inline void __depsan_atomic_long_fetch_add_e(void) { }
static inline void __depsan_atomic_long_fetch_add_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_add_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_add_release_e(void) { }

static inline void __depsan_atomic_fetch_inc_e(void) { }
static inline void __depsan_atomic_fetch_inc_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_inc_acquire_e(void) { }
static inline void __depsan_atomic_fetch_inc_release_e(void) { }

static inline void __depsan_atomic_long_fetch_inc_e(void) { }
static inline void __depsan_atomic_long_fetch_inc_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_inc_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_inc_release_e(void) { }

static inline void __depsan_atomic_fetch_sub_e(void) { }
static inline void __depsan_atomic_fetch_sub_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_sub_acquire_e(void) { }
static inline void __depsan_atomic_fetch_sub_release_e(void) { }

static inline void __depsan_atomic_long_fetch_sub_e(void) { }
static inline void __depsan_atomic_long_fetch_sub_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_sub_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_sub_release_e(void) { }

static inline void __depsan_atomic_fetch_dec_e(void) { }
static inline void __depsan_atomic_fetch_dec_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_dec_acquire_e(void) { }
static inline void __depsan_atomic_fetch_dec_release_e(void) { }

static inline void __depsan_atomic_long_fetch_dec_e(void) { }
static inline void __depsan_atomic_long_fetch_dec_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_dec_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_dec_release_e(void) { }

static inline void __depsan_atomic_fetch_and_e(void) { }
static inline void __depsan_atomic_fetch_and_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_and_acquire_e(void) { }
static inline void __depsan_atomic_fetch_and_release_e(void) { }

static inline void __depsan_atomic_long_fetch_and_e(void) { }
static inline void __depsan_atomic_long_fetch_and_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_and_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_and_release_e(void) { }

static inline void __depsan_atomic_fetch_andnot_e(void) { }
static inline void __depsan_atomic_fetch_andnot_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_andnot_acquire_e(void) { }
static inline void __depsan_atomic_fetch_andnot_release_e(void) { }

static inline void __depsan_atomic_long_fetch_andnot_e(void) { }
static inline void __depsan_atomic_long_fetch_andnot_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_andnot_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_andnot_release_e(void) { }

static inline void __depsan_atomic_fetch_or_e(void) { }
static inline void __depsan_atomic_fetch_or_relaxed_e(void) { }
static inline void __depsan_atomic_fetch_or_acquire_e(void) { }
static inline void __depsan_atomic_fetch_or_release_e(void) { }

static inline void __depsan_atomic_long_fetch_or_e(void) { }
static inline void __depsan_atomic_long_fetch_or_relaxed_e(void) { }
static inline void __depsan_atomic_long_fetch_or_acquire_e(void) { }
static inline void __depsan_atomic_long_fetch_or_release_e(void) { }

static inline void __depsan_atomic_add_return_e(void) { }
static inline void __depsan_atomic_add_return_relaxed_e(void) { }
static inline void __depsan_atomic_add_return_acquire_e(void) { }
static inline void __depsan_atomic_add_return_release_e(void) { }

static inline void __depsan_atomic_inc_return_e(void) { }
static inline void __depsan_atomic_inc_return_relaxed_e(void) { }
static inline void __depsan_atomic_inc_return_acquire_e(void) { }
static inline void __depsan_atomic_inc_return_release_e(void) { }

static inline void __depsan_atomic_long_inc_return_e(void) { }
static inline void __depsan_atomic_long_inc_return_relaxed_e(void) { }
static inline void __depsan_atomic_long_inc_return_acquire_e(void) { }
static inline void __depsan_atomic_long_inc_return_release_e(void) { }

static inline void __depsan_atomic_sub_return_e(void) { }
static inline void __depsan_atomic_sub_return_relaxed_e(void) { }
static inline void __depsan_atomic_sub_return_acquire_e(void) { }
static inline void __depsan_atomic_sub_return_release_e(void) { }

static inline void __depsan_atomic_long_sub_return_e(void) { }
static inline void __depsan_atomic_long_sub_return_relaxed_e(void) { }
static inline void __depsan_atomic_long_sub_return_acquire_e(void) { }
static inline void __depsan_atomic_long_sub_return_release_e(void) { }

static inline void __depsan_atomic_dec_return_e(void) { }
static inline void __depsan_atomic_dec_return_relaxed_e(void) { }
static inline void __depsan_atomic_dec_return_acquire_e(void) { }
static inline void __depsan_atomic_dec_return_release_e(void) { }

static inline void __depsan_atomic_long_dec_return_e(void) { }
static inline void __depsan_atomic_long_dec_return_relaxed_e(void) { }
static inline void __depsan_atomic_long_dec_return_acquire_e(void) { }
static inline void __depsan_atomic_long_dec_return_release_e(void) { }

static inline void __depsan_atomic_xchg_e(void) { }
static inline void __depsan_atomic_xchg_relaxed_e(void) { }
static inline void __depsan_atomic_xchg_release_e(void) { }
static inline void __depsan_atomic_xchg_acquire_e(void) { }

static inline void __depsan_atomic_long_xchg_e(void) { }
static inline void __depsan_atomic_long_xchg_relaxed_e(void) { }
static inline void __depsan_atomic_long_xchg_release_e(void) { }
static inline void __depsan_atomic_long_xchg_acquire_e(void) { }

static inline void __depsan_atomic_cmpxchg_e(void) { }
static inline void __depsan_atomic_cmpxchg_relaxed_e(void) { }
static inline void __depsan_atomic_cmpxchg_acquire_e(void) { }
static inline void __depsan_atomic_cmpxchg_release_e(void) { }

static inline void __depsan_atomic_long_cmpxchg_e(void) { }
static inline void __depsan_atomic_long_cmpxchg_relaxed_e(void) { }
static inline void __depsan_atomic_long_cmpxchg_acquire_e(void) { }
static inline void __depsan_atomic_long_cmpxchg_release_e(void) { }

static inline void __depsan_atomic_sub_and_test_e(void) { }
static inline void __depsan_atomic_dec_and_test_e(void) { }
static inline void __depsan_atomic_inc_and_test_e(void) { }
static inline void __depsan_atomic_add_negative_e(void) { }

static inline void __depsan_atomic_long_sub_and_test_e(void) { }
static inline void __depsan_atomic_long_dec_and_test_e(void) { }
static inline void __depsan_atomic_long_inc_and_test_e(void) { }
static inline void __depsan_atomic_long_add_negative_e(void) { }

#ifdef CONFIG_DEPSAN

#define mark_depsan_mb_b()		__depsan_mb_b()
#define mark_depsan_mb_e()		__depsan_mb_e()
#define mark_depsan_mb_ba_b()		__depsan_mb_ba_b()
#define mark_depsan_mb_ba_e()		__depsan_mb_ba_e()
#define mark_depsan_mb_aa_b()		__depsan_mb_aa_b()
#define mark_depsan_mb_aa_e()		__depsan_mb_aa_e()
#define mark_depsan_wmb_b()		__depsan_wmb_b()
#define mark_depsan_wmb_e()		__depsan_wmb_e()
#define mark_depsan_rmb_b()		__depsan_rmb_b()
#define mark_depsan_rmb_e()		__depsan_rmb_e()
#define mark_depsan_s_release_b()	__depsan_s_release_b()
#define mark_depsan_s_release_e()	__depsan_s_release_e()
#define mark_depsan_l_acquire_b()	__depsan_l_acquire_b()
#define mark_depsan_l_acquire_e()	__depsan_l_acquire_e()
#define mark_depsan_atomic_b()		__depsan_atomic_b()
#define mark_depsan_atomic_e()		__depsan_atomic_e()
#define mark_depsan_ronce_b()		__depsan_ronce_b()
#define mark_depsan_ronce_e()		__depsan_ronce_e()
#define mark_depsan_wonce_b()		__depsan_wonce_b()
#define mark_depsan_wonce_e()		__depsan_wonce_e()
#define mark_depsan_lock_b()		__depsan_lock_b()
#define mark_depsan_lock_e()		__depsan_lock_e()
#define mark_depsan_unlock_b()		__depsan_unlock_b()
#define mark_depsan_unlock_e()		__depsan_unlock_e()

#define mark_depsan_rcu_deref_b()	__depsan_rcu_deref_b()
#define mark_depsan_rcu_deref_e()	__depsan_rcu_deref_e()
#define mark_depsan_rcu_assign_b()	__depsan_rcu_assign_b()
#define mark_depsan_rcu_assign_e()	__depsan_rcu_assign_e()
#define mark_depsan_rcu_sync_b()	__depsan_rcu_sync_b()
#define mark_depsan_rcu_sync_e()	__depsan_rcu_sync_e()

/** Begin **/
/* Basic operations */
#define mark_depsan_atomic_read_b()	__depsan_atomic_read_b()
#define mark_depsan_atomic_set_b()	__depsan_atomic_set_b()
#define mark_depsan_atomic_read_acquire_b()	__depsan_atomic_read_acquire_b()
#define mark_depsan_atomic_set_release_b()	__depsan_atomic_set_release_b()

#define mark_depsan_atomic_long_read_b()	__depsan_atomic_long_read_b()
#define mark_depsan_atomic_long_set_b()	__depsan_atomic_long_set_b()
#define mark_depsan_atomic_long_read_acquire_b()	__depsan_atomic_long_read_acquire_b()
#define mark_depsan_atomic_long_set_release_b()	__depsan_atomic_long_set_release_b()

/* Non-value-returning atomics */
#define mark_depsan_atomic_add_b()	__depsan_atomic_add_b()
#define mark_depsan_atomic_sub_b()	__depsan_atomic_sub_b()
#define mark_depsan_atomic_inc_b()	__depsan_atomic_inc_b()
#define mark_depsan_atomic_dec_b()	__depsan_atomic_dec_b()
#define mark_depsan_atomic_and_b()	__depsan_atomic_and_b()
#define mark_depsan_atomic_andnot_b()	__depsan_atomic_andnot_b()
#define mark_depsan_atomic_or_b()	__depsan_atomic_or_b()

#define mark_depsan_atomic_long_add_b()	__depsan_atomic_long_add_b()
#define mark_depsan_atomic_long_sub_b()	__depsan_atomic_long_sub_b()
#define mark_depsan_atomic_long_inc_b()	__depsan_atomic_long_inc_b()
#define mark_depsan_atomic_long_dec_b()	__depsan_atomic_long_dec_b()
#define mark_depsan_atomic_long_and_b()	__depsan_atomic_long_and_b()
#define mark_depsan_atomic_long_andnot_b()	__depsan_atomic_long_andnot_b()
#define mark_depsan_atomic_long_or_b()	__depsan_atomic_long_or_b()

/* Value-returning atomics */

#define mark_depsan_atomic_fetch_add_b()	__depsan_atomic_fetch_add_b()
#define mark_depsan_atomic_xadd_b()		__depsan_atomic_xadd_b()
#define mark_depsan_atomic_fetch_add_relaxed_b()	__depsan_atomic_fetch_add_relaxed_b()
#define mark_depsan_atomic_fetch_add_acquire_b()	__depsan_atomic_fetch_add_acquire_b()
#define mark_depsan_atomic_fetch_add_release_b()	__depsan_atomic_fetch_add_release_b()

#define mark_depsan_atomic_long_fetch_add_b()	__depsan_atomic_long_fetch_add_b()
#define mark_depsan_atomic_long_fetch_add_relaxed_b()	__depsan_atomic_long_fetch_add_relaxed_b()
#define mark_depsan_atomic_long_fetch_add_acquire_b()	__depsan_atomic_long_fetch_add_acquire_b()
#define mark_depsan_atomic_long_fetch_add_release_b()	__depsan_atomic_long_fetch_add_release_b()

#define mark_depsan_atomic_fetch_inc_b()	__depsan_atomic_fetch_inc_b()
#define mark_depsan_atomic_fetch_inc_relaxed_b()	__depsan_atomic_fetch_inc_relaxed_b()
#define mark_depsan_atomic_fetch_inc_acquire_b()	__depsan_atomic_fetch_inc_acquire_b()
#define mark_depsan_atomic_fetch_inc_release_b()	__depsan_atomic_fetch_inc_release_b()

#define mark_depsan_atomic_long_fetch_inc_b()	__depsan_atomic_long_fetch_inc_b()
#define mark_depsan_atomic_long_fetch_inc_relaxed_b()	__depsan_atomic_long_fetch_inc_relaxed_b()
#define mark_depsan_atomic_long_fetch_inc_acquire_b()	__depsan_atomic_long_fetch_inc_acquire_b()
#define mark_depsan_atomic_long_fetch_inc_release_b()	__depsan_atomic_long_fetch_inc_release_b()

#define mark_depsan_atomic_fetch_sub_b()	__depsan_atomic_fetch_sub_b()
#define mark_depsan_atomic_fetch_sub_relaxed_b()	__depsan_atomic_fetch_sub_relaxed_b()
#define mark_depsan_atomic_fetch_sub_acquire_b()	__depsan_atomic_fetch_sub_acquire_b()
#define mark_depsan_atomic_fetch_sub_release_b()	__depsan_atomic_fetch_sub_release_b()

#define mark_depsan_atomic_long_fetch_sub_b()	__depsan_atomic_long_fetch_sub_b()
#define mark_depsan_atomic_long_fetch_sub_relaxed_b()	__depsan_atomic_long_fetch_sub_relaxed_b()
#define mark_depsan_atomic_long_fetch_sub_acquire_b()	__depsan_atomic_long_fetch_sub_acquire_b()
#define mark_depsan_atomic_long_fetch_sub_release_b()	__depsan_atomic_long_fetch_sub_release_b()

#define mark_depsan_atomic_fetch_dec_b()	__depsan_atomic_fetch_dec_b()
#define mark_depsan_atomic_fetch_dec_relaxed_b()	__depsan_atomic_fetch_dec_relaxed_b()
#define mark_depsan_atomic_fetch_dec_acquire_b()	__depsan_atomic_fetch_dec_acquire_b()
#define mark_depsan_atomic_fetch_dec_release_b()	__depsan_atomic_fetch_dec_release_b()

#define mark_depsan_atomic_long_fetch_dec_b()	__depsan_atomic_long_fetch_dec_b()
#define mark_depsan_atomic_long_fetch_dec_relaxed_b()	__depsan_atomic_long_fetch_dec_relaxed_b()
#define mark_depsan_atomic_long_fetch_dec_acquire_b()	__depsan_atomic_long_fetch_dec_acquire_b()
#define mark_depsan_atomic_long_fetch_dec_release_b()	__depsan_atomic_long_fetch_dec_release_b()

#define mark_depsan_atomic_fetch_and_b()	__depsan_atomic_fetch_and_b()
#define mark_depsan_atomic_fetch_and_relaxed_b()	__depsan_atomic_fetch_and_relaxed_b()
#define mark_depsan_atomic_fetch_and_acquire_b()	__depsan_atomic_fetch_and_acquire_b()
#define mark_depsan_atomic_fetch_and_release_b()	__depsan_atomic_fetch_and_release_b()

#define mark_depsan_atomic_long_fetch_and_b()	__depsan_atomic_long_fetch_and_b()
#define mark_depsan_atomic_long_fetch_and_relaxed_b()	__depsan_atomic_long_fetch_and_relaxed_b()
#define mark_depsan_atomic_long_fetch_and_acquire_b()	__depsan_atomic_long_fetch_and_acquire_b()
#define mark_depsan_atomic_long_fetch_and_release_b()	__depsan_atomic_long_fetch_and_release_b()

#define mark_depsan_atomic_fetch_andnot_b()	__depsan_atomic_fetch_andnot_b()
#define mark_depsan_atomic_fetch_andnot_relaxed_b()	__depsan_atomic_fetch_andnot_relaxed_b()
#define mark_depsan_atomic_fetch_andnot_acquire_b()	__depsan_atomic_fetch_andnot_acquire_b()
#define mark_depsan_atomic_fetch_andnot_release_b()	__depsan_atomic_fetch_andnot_release_b()

#define mark_depsan_atomic_long_fetch_andnot_b()	__depsan_atomic_long_fetch_andnot_b()
#define mark_depsan_atomic_long_fetch_andnot_relaxed_b()	__depsan_atomic_long_fetch_andnot_relaxed_b()
#define mark_depsan_atomic_long_fetch_andnot_acquire_b()	__depsan_atomic_long_fetch_andnot_acquire_b()
#define mark_depsan_atomic_long_fetch_andnot_release_b()	__depsan_atomic_long_fetch_andnot_release_b()

#define mark_depsan_atomic_fetch_or_b()	__depsan_atomic_fetch_or_b()
#define mark_depsan_atomic_fetch_or_relaxed_b()	__depsan_atomic_fetch_or_relaxed_b()
#define mark_depsan_atomic_fetch_or_acquire_b()	__depsan_atomic_fetch_or_acquire_b()
#define mark_depsan_atomic_fetch_or_release_b()	__depsan_atomic_fetch_or_release_b()

#define mark_depsan_atomic_long_fetch_or_b()	__depsan_atomic_long_fetch_or_b()
#define mark_depsan_atomic_long_fetch_or_relaxed_b()	__depsan_atomic_long_fetch_or_relaxed_b()
#define mark_depsan_atomic_long_fetch_or_acquire_b()	__depsan_atomic_long_fetch_or_acquire_b()
#define mark_depsan_atomic_long_fetch_or_release_b()	__depsan_atomic_long_fetch_or_release_b()

#define mark_depsan_atomic_add_return_b()	__depsan_atomic_add_return_b()
#define mark_depsan_atomic_add_return_relaxed_b()	__depsan_atomic_add_return_relaxed_b()
#define mark_depsan_atomic_add_return_acquire_b()	__depsan_atomic_add_return_acquire_b()
#define mark_depsan_atomic_add_return_release_b()	__depsan_atomic_add_return_release_b()

#define mark_depsan_atomic_inc_return_b()	__depsan_atomic_inc_return_b()
#define mark_depsan_atomic_inc_return_relaxed_b()	__depsan_atomic_inc_return_relaxed_b()
#define mark_depsan_atomic_inc_return_acquire_b()	__depsan_atomic_inc_return_acquire_b()
#define mark_depsan_atomic_inc_return_release_b()	__depsan_atomic_inc_return_release_b()

#define mark_depsan_atomic_long_inc_return_b()	__depsan_atomic_long_inc_return_b()
#define mark_depsan_atomic_long_inc_return_relaxed_b()	__depsan_atomic_long_inc_return_relaxed_b()
#define mark_depsan_atomic_long_inc_return_acquire_b()	__depsan_atomic_long_inc_return_acquire_b()
#define mark_depsan_atomic_long_inc_return_release_b()	__depsan_atomic_long_inc_return_release_b()

#define mark_depsan_atomic_sub_return_b()	__depsan_atomic_sub_return_b()
#define mark_depsan_atomic_sub_return_relaxed_b()	__depsan_atomic_sub_return_relaxed_b()
#define mark_depsan_atomic_sub_return_acquire_b()	__depsan_atomic_sub_return_acquire_b()
#define mark_depsan_atomic_sub_return_release_b()	__depsan_atomic_sub_return_release_b()

#define mark_depsan_atomic_long_sub_return_b()	__depsan_atomic_long_sub_return_b()
#define mark_depsan_atomic_long_sub_return_relaxed_b()	__depsan_atomic_long_sub_return_relaxed_b()
#define mark_depsan_atomic_long_sub_return_acquire_b()	__depsan_atomic_long_sub_return_acquire_b()
#define mark_depsan_atomic_long_sub_return_release_b()	__depsan_atomic_long_sub_return_release_b()

#define mark_depsan_atomic_dec_return_b()	__depsan_atomic_dec_return_b()
#define mark_depsan_atomic_dec_return_relaxed_b()	__depsan_atomic_dec_return_relaxed_b()
#define mark_depsan_atomic_dec_return_acquire_b()	__depsan_atomic_dec_return_acquire_b()
#define mark_depsan_atomic_dec_return_release_b()	__depsan_atomic_dec_return_release_b()

#define mark_depsan_atomic_long_dec_return_b()	__depsan_atomic_long_dec_return_b()
#define mark_depsan_atomic_long_dec_return_relaxed_b()	__depsan_atomic_long_dec_return_relaxed_b()
#define mark_depsan_atomic_long_dec_return_acquire_b()	__depsan_atomic_long_dec_return_acquire_b()
#define mark_depsan_atomic_long_dec_return_release_b()	__depsan_atomic_long_dec_return_release_b()

#define mark_depsan_atomic_xchg_b()	__depsan_atomic_xchg_b()
#define mark_depsan_atomic_xchg_relaxed_b()	__depsan_atomic_xchg_relaxed_b()
#define mark_depsan_atomic_xchg_release_b()	__depsan_atomic_xchg_release_b()
#define mark_depsan_atomic_xchg_acquire_b()	__depsan_atomic_xchg_acquire_b()

#define mark_depsan_atomic_long_xchg_b()	__depsan_atomic_long_xchg_b()
#define mark_depsan_atomic_long_xchg_relaxed_b()	__depsan_atomic_long_xchg_relaxed_b()
#define mark_depsan_atomic_long_xchg_release_b()	__depsan_atomic_long_xchg_release_b()
#define mark_depsan_atomic_long_xchg_acquire_b()	__depsan_atomic_long_xchg_acquire_b()

#define mark_depsan_atomic_cmpxchg_b()	__depsan_atomic_cmpxchg_b()
#define mark_depsan_atomic_cmpxchg_relaxed_b()	__depsan_atomic_cmpxchg_relaxed_b()
#define mark_depsan_atomic_cmpxchg_acquire_b()	__depsan_atomic_cmpxchg_acquire_b()
#define mark_depsan_atomic_cmpxchg_release_b()	__depsan_atomic_cmpxchg_release_b()

#define mark_depsan_atomic_long_cmpxchg_b()	__depsan_atomic_long_cmpxchg_b()
#define mark_depsan_atomic_long_cmpxchg_relaxed_b()	__depsan_atomic_long_cmpxchg_relaxed_b()
#define mark_depsan_atomic_long_cmpxchg_acquire_b()	__depsan_atomic_long_cmpxchg_acquire_b()
#define mark_depsan_atomic_long_cmpxchg_release_b()	__depsan_atomic_long_cmpxchg_release_b()

#define mark_depsan_atomic_sub_and_test_b()	__depsan_atomic_sub_and_test_b()
#define mark_depsan_atomic_dec_and_test_b()	__depsan_atomic_dec_and_test_b()
#define mark_depsan_atomic_inc_and_test_b()	__depsan_atomic_inc_and_test_b()
#define mark_depsan_atomic_add_negative_b()	__depsan_atomic_add_negative_b()

#define mark_depsan_atomic_long_sub_and_test_b()	__depsan_atomic_long_sub_and_test_b()
#define mark_depsan_atomic_long_dec_and_test_b()	__depsan_atomic_long_dec_and_test_b()
#define mark_depsan_atomic_long_inc_and_test_b()	__depsan_atomic_long_inc_and_test_b()
#define mark_depsan_atomic_long_add_negative_b()	__depsan_atomic_long_add_negative_b()

/** End **/
/* Basic operations */
#define mark_depsan_atomic_read_e()	__depsan_atomic_read_e()
#define mark_depsan_atomic_set_e()	__depsan_atomic_set_e()
#define mark_depsan_atomic_read_acquire_e()	__depsan_atomic_read_acquire_e()
#define mark_depsan_atomic_set_release_e()	__depsan_atomic_set_release_e()

#define mark_depsan_atomic_long_read_e()	__depsan_atomic_long_read_e()
#define mark_depsan_atomic_long_set_e()	__depsan_atomic_long_set_e()
#define mark_depsan_atomic_long_read_acquire_e()	__depsan_atomic_long_read_acquire_e()
#define mark_depsan_atomic_long_set_release_e()	__depsan_atomic_long_set_release_e()

/* Non-value-returning atomics */
#define mark_depsan_atomic_add_e()	__depsan_atomic_add_e()
#define mark_depsan_atomic_sub_e()	__depsan_atomic_sub_e()
#define mark_depsan_atomic_inc_e()	__depsan_atomic_inc_e()
#define mark_depsan_atomic_dec_e()	__depsan_atomic_dec_e()
#define mark_depsan_atomic_and_e()	__depsan_atomic_and_e()
#define mark_depsan_atomic_andnot_e()	__depsan_atomic_andnot_e()
#define mark_depsan_atomic_or_e()	__depsan_atomic_or_e()

#define mark_depsan_atomic_long_add_e()	__depsan_atomic_long_add_e()
#define mark_depsan_atomic_long_sub_e()	__depsan_atomic_long_sub_e()
#define mark_depsan_atomic_long_inc_e()	__depsan_atomic_long_inc_e()
#define mark_depsan_atomic_long_dec_e()	__depsan_atomic_long_dec_e()
#define mark_depsan_atomic_long_and_e()	__depsan_atomic_long_and_e()
#define mark_depsan_atomic_long_andnot_e()	__depsan_atomic_long_andnot_e()
#define mark_depsan_atomic_long_or_e()	__depsan_atomic_long_or_e()

/* Value-returning atomics */

#define mark_depsan_atomic_fetch_add_e()	__depsan_atomic_fetch_add_e()
#define mark_depsan_atomic_xadd_e()		__depsan_atomic_xadd_e()
#define mark_depsan_atomic_fetch_add_relaxed_e()	__depsan_atomic_fetch_add_relaxed_e()
#define mark_depsan_atomic_fetch_add_acquire_e()	__depsan_atomic_fetch_add_acquire_e()
#define mark_depsan_atomic_fetch_add_release_e()	__depsan_atomic_fetch_add_release_e()

#define mark_depsan_atomic_long_fetch_add_e()	__depsan_atomic_long_fetch_add_e()
#define mark_depsan_atomic_long_fetch_add_relaxed_e()	__depsan_atomic_long_fetch_add_relaxed_e()
#define mark_depsan_atomic_long_fetch_add_acquire_e()	__depsan_atomic_long_fetch_add_acquire_e()
#define mark_depsan_atomic_long_fetch_add_release_e()	__depsan_atomic_long_fetch_add_release_e()

#define mark_depsan_atomic_fetch_inc_e()	__depsan_atomic_fetch_inc_e()
#define mark_depsan_atomic_fetch_inc_relaxed_e()	__depsan_atomic_fetch_inc_relaxed_e()
#define mark_depsan_atomic_fetch_inc_acquire_e()	__depsan_atomic_fetch_inc_acquire_e()
#define mark_depsan_atomic_fetch_inc_release_e()	__depsan_atomic_fetch_inc_release_e()

#define mark_depsan_atomic_long_fetch_inc_e()	__depsan_atomic_long_fetch_inc_e()
#define mark_depsan_atomic_long_fetch_inc_relaxed_e()	__depsan_atomic_long_fetch_inc_relaxed_e()
#define mark_depsan_atomic_long_fetch_inc_acquire_e()	__depsan_atomic_long_fetch_inc_acquire_e()
#define mark_depsan_atomic_long_fetch_inc_release_e()	__depsan_atomic_long_fetch_inc_release_e()

#define mark_depsan_atomic_fetch_sub_e()	__depsan_atomic_fetch_sub_e()
#define mark_depsan_atomic_fetch_sub_relaxed_e()	__depsan_atomic_fetch_sub_relaxed_e()
#define mark_depsan_atomic_fetch_sub_acquire_e()	__depsan_atomic_fetch_sub_acquire_e()
#define mark_depsan_atomic_fetch_sub_release_e()	__depsan_atomic_fetch_sub_release_e()

#define mark_depsan_atomic_long_fetch_sub_e()	__depsan_atomic_long_fetch_sub_e()
#define mark_depsan_atomic_long_fetch_sub_relaxed_e()	__depsan_atomic_long_fetch_sub_relaxed_e()
#define mark_depsan_atomic_long_fetch_sub_acquire_e()	__depsan_atomic_long_fetch_sub_acquire_e()
#define mark_depsan_atomic_long_fetch_sub_release_e()	__depsan_atomic_long_fetch_sub_release_e()

#define mark_depsan_atomic_fetch_dec_e()	__depsan_atomic_fetch_dec_e()
#define mark_depsan_atomic_fetch_dec_relaxed_e()	__depsan_atomic_fetch_dec_relaxed_e()
#define mark_depsan_atomic_fetch_dec_acquire_e()	__depsan_atomic_fetch_dec_acquire_e()
#define mark_depsan_atomic_fetch_dec_release_e()	__depsan_atomic_fetch_dec_release_e()

#define mark_depsan_atomic_long_fetch_dec_e()	__depsan_atomic_long_fetch_dec_e()
#define mark_depsan_atomic_long_fetch_dec_relaxed_e()	__depsan_atomic_long_fetch_dec_relaxed_e()
#define mark_depsan_atomic_long_fetch_dec_acquire_e()	__depsan_atomic_long_fetch_dec_acquire_e()
#define mark_depsan_atomic_long_fetch_dec_release_e()	__depsan_atomic_long_fetch_dec_release_e()

#define mark_depsan_atomic_fetch_and_e()	__depsan_atomic_fetch_and_e()
#define mark_depsan_atomic_fetch_and_relaxed_e()	__depsan_atomic_fetch_and_relaxed_e()
#define mark_depsan_atomic_fetch_and_acquire_e()	__depsan_atomic_fetch_and_acquire_e()
#define mark_depsan_atomic_fetch_and_release_e()	__depsan_atomic_fetch_and_release_e()

#define mark_depsan_atomic_long_fetch_and_e()	__depsan_atomic_long_fetch_and_e()
#define mark_depsan_atomic_long_fetch_and_relaxed_e()	__depsan_atomic_long_fetch_and_relaxed_e()
#define mark_depsan_atomic_long_fetch_and_acquire_e()	__depsan_atomic_long_fetch_and_acquire_e()
#define mark_depsan_atomic_long_fetch_and_release_e()	__depsan_atomic_long_fetch_and_release_e()

#define mark_depsan_atomic_fetch_andnot_e()	__depsan_atomic_fetch_andnot_e()
#define mark_depsan_atomic_fetch_andnot_relaxed_e()	__depsan_atomic_fetch_andnot_relaxed_e()
#define mark_depsan_atomic_fetch_andnot_acquire_e()	__depsan_atomic_fetch_andnot_acquire_e()
#define mark_depsan_atomic_fetch_andnot_release_e()	__depsan_atomic_fetch_andnot_release_e()

#define mark_depsan_atomic_long_fetch_andnot_e()	__depsan_atomic_long_fetch_andnot_e()
#define mark_depsan_atomic_long_fetch_andnot_relaxed_e()	__depsan_atomic_long_fetch_andnot_relaxed_e()
#define mark_depsan_atomic_long_fetch_andnot_acquire_e()	__depsan_atomic_long_fetch_andnot_acquire_e()
#define mark_depsan_atomic_long_fetch_andnot_release_e()	__depsan_atomic_long_fetch_andnot_release_e()

#define mark_depsan_atomic_fetch_or_e()	__depsan_atomic_fetch_or_e()
#define mark_depsan_atomic_fetch_or_relaxed_e()	__depsan_atomic_fetch_or_relaxed_e()
#define mark_depsan_atomic_fetch_or_acquire_e()	__depsan_atomic_fetch_or_acquire_e()
#define mark_depsan_atomic_fetch_or_release_e()	__depsan_atomic_fetch_or_release_e()

#define mark_depsan_atomic_long_fetch_or_e()	__depsan_atomic_long_fetch_or_e()
#define mark_depsan_atomic_long_fetch_or_relaxed_e()	__depsan_atomic_long_fetch_or_relaxed_e()
#define mark_depsan_atomic_long_fetch_or_acquire_e()	__depsan_atomic_long_fetch_or_acquire_e()
#define mark_depsan_atomic_long_fetch_or_release_e()	__depsan_atomic_long_fetch_or_release_e()

#define mark_depsan_atomic_add_return_e()	__depsan_atomic_add_return_e()
#define mark_depsan_atomic_add_return_relaxed_e()	__depsan_atomic_add_return_relaxed_e()
#define mark_depsan_atomic_add_return_acquire_e()	__depsan_atomic_add_return_acquire_e()
#define mark_depsan_atomic_add_return_release_e()	__depsan_atomic_add_return_release_e()

#define mark_depsan_atomic_inc_return_e()	__depsan_atomic_inc_return_e()
#define mark_depsan_atomic_inc_return_relaxed_e()	__depsan_atomic_inc_return_relaxed_e()
#define mark_depsan_atomic_inc_return_acquire_e()	__depsan_atomic_inc_return_acquire_e()
#define mark_depsan_atomic_inc_return_release_e()	__depsan_atomic_inc_return_release_e()

#define mark_depsan_atomic_long_inc_return_e()	__depsan_atomic_long_inc_return_e()
#define mark_depsan_atomic_long_inc_return_relaxed_e()	__depsan_atomic_long_inc_return_relaxed_e()
#define mark_depsan_atomic_long_inc_return_acquire_e()	__depsan_atomic_long_inc_return_acquire_e()
#define mark_depsan_atomic_long_inc_return_release_e()	__depsan_atomic_long_inc_return_release_e()

#define mark_depsan_atomic_sub_return_e()	__depsan_atomic_sub_return_e()
#define mark_depsan_atomic_sub_return_relaxed_e()	__depsan_atomic_sub_return_relaxed_e()
#define mark_depsan_atomic_sub_return_acquire_e()	__depsan_atomic_sub_return_acquire_e()
#define mark_depsan_atomic_sub_return_release_e()	__depsan_atomic_sub_return_release_e()

#define mark_depsan_atomic_long_sub_return_e()	__depsan_atomic_long_sub_return_e()
#define mark_depsan_atomic_long_sub_return_relaxed_e()	__depsan_atomic_long_sub_return_relaxed_e()
#define mark_depsan_atomic_long_sub_return_acquire_e()	__depsan_atomic_long_sub_return_acquire_e()
#define mark_depsan_atomic_long_sub_return_release_e()	__depsan_atomic_long_sub_return_release_e()

#define mark_depsan_atomic_dec_return_e()	__depsan_atomic_dec_return_e()
#define mark_depsan_atomic_dec_return_relaxed_e()	__depsan_atomic_dec_return_relaxed_e()
#define mark_depsan_atomic_dec_return_acquire_e()	__depsan_atomic_dec_return_acquire_e()
#define mark_depsan_atomic_dec_return_release_e()	__depsan_atomic_dec_return_release_e()

#define mark_depsan_atomic_long_dec_return_e()	__depsan_atomic_long_dec_return_e()
#define mark_depsan_atomic_long_dec_return_relaxed_e()	__depsan_atomic_long_dec_return_relaxed_e()
#define mark_depsan_atomic_long_dec_return_acquire_e()	__depsan_atomic_long_dec_return_acquire_e()
#define mark_depsan_atomic_long_dec_return_release_e()	__depsan_atomic_long_dec_return_release_e()

#define mark_depsan_atomic_xchg_e()	__depsan_atomic_xchg_e()
#define mark_depsan_atomic_xchg_relaxed_e()	__depsan_atomic_xchg_relaxed_e()
#define mark_depsan_atomic_xchg_release_e()	__depsan_atomic_xchg_release_e()
#define mark_depsan_atomic_xchg_acquire_e()	__depsan_atomic_xchg_acquire_e()

#define mark_depsan_atomic_long_xchg_e()	__depsan_atomic_long_xchg_e()
#define mark_depsan_atomic_long_xchg_relaxed_e()	__depsan_atomic_long_xchg_relaxed_e()
#define mark_depsan_atomic_long_xchg_release_e()	__depsan_atomic_long_xchg_release_e()
#define mark_depsan_atomic_long_xchg_acquire_e()	__depsan_atomic_long_xchg_acquire_e()

#define mark_depsan_atomic_cmpxchg_e()	__depsan_atomic_cmpxchg_e()
#define mark_depsan_atomic_cmpxchg_relaxed_e()	__depsan_atomic_cmpxchg_relaxed_e()
#define mark_depsan_atomic_cmpxchg_acquire_e()	__depsan_atomic_cmpxchg_acquire_e()
#define mark_depsan_atomic_cmpxchg_release_e()	__depsan_atomic_cmpxchg_release_e()

#define mark_depsan_atomic_long_cmpxchg_e()	__depsan_atomic_long_cmpxchg_e()
#define mark_depsan_atomic_long_cmpxchg_relaxed_e()	__depsan_atomic_long_cmpxchg_relaxed_e()
#define mark_depsan_atomic_long_cmpxchg_acquire_e()	__depsan_atomic_long_cmpxchg_acquire_e()
#define mark_depsan_atomic_long_cmpxchg_release_e()	__depsan_atomic_long_cmpxchg_release_e()

#define mark_depsan_atomic_sub_and_test_e()	__depsan_atomic_sub_and_test_e()
#define mark_depsan_atomic_dec_and_test_e()	__depsan_atomic_dec_and_test_e()
#define mark_depsan_atomic_inc_and_test_e()	__depsan_atomic_inc_and_test_e()
#define mark_depsan_atomic_add_negative_e()	__depsan_atomic_add_negative_e()

#define mark_depsan_atomic_long_sub_and_test_e()	__depsan_atomic_long_sub_and_test_e()
#define mark_depsan_atomic_long_dec_and_test_e()	__depsan_atomic_long_dec_and_test_e()
#define mark_depsan_atomic_long_inc_and_test_e()	__depsan_atomic_long_inc_and_test_e()
#define mark_depsan_atomic_long_add_negative_e()	__depsan_atomic_long_add_negative_e()

#else /* CONFIG_DEPSAN */

#define mark_depsan_mb_b()
#define mark_depsan_mb_e()
#define mark_depsan_mb_ba_b()
#define mark_depsan_mb_ba_e()
#define mark_depsan_mb_aa_b()
#define mark_depsan_mb_aa_e()
#define mark_depsan_wmb_b()
#define mark_depsan_wmb_e()
#define mark_depsan_rmb_b()
#define mark_depsan_rmb_e()
#define mark_depsan_s_release_b()
#define mark_depsan_s_release_e()
#define mark_depsan_l_acquire_b()
#define mark_depsan_l_acquire_e()
#define mark_depsan_atomic_b()
#define mark_depsan_atomic_e()
#define mark_depsan_ronce_b()
#define mark_depsan_ronce_e()
#define mark_depsan_wonce_b()
#define mark_depsan_wonce_e()
#define mark_depsan_lock_b()
#define mark_depsan_lock_e()
#define mark_depsan_unlock_b()
#define mark_depsan_unlock_e()

#define mark_depsan_rcu_deref_b()
#define mark_depsan_rcu_deref_e()
#define mark_depsan_rcu_assign_b()
#define mark_depsan_rcu_assign_e()
#define mark_depsan_rcu_sync_b()
#define mark_depsan_rcu_sync_e()

/** Begin **/
/* Basic operations */
#define mark_depsan_atomic_read_b()
#define mark_depsan_atomic_set_b()
#define mark_depsan_atomic_read_acquire_b()
#define mark_depsan_atomic_set_release_b()

#define mark_depsan_atomic_long_read_b()
#define mark_depsan_atomic_long_set_b()
#define mark_depsan_atomic_long_read_acquire_b()
#define mark_depsan_atomic_long_set_release_b()

/* Non-value-returning atomics */
#define mark_depsan_atomic_add_b()
#define mark_depsan_atomic_sub_b()
#define mark_depsan_atomic_inc_b()
#define mark_depsan_atomic_dec_b()
#define mark_depsan_atomic_and_b()
#define mark_depsan_atomic_andnot_b()
#define mark_depsan_atomic_or_b()

#define mark_depsan_atomic_long_add_b()
#define mark_depsan_atomic_long_sub_b()
#define mark_depsan_atomic_long_inc_b()
#define mark_depsan_atomic_long_dec_b()
#define mark_depsan_atomic_long_and_b()
#define mark_depsan_atomic_long_andnot_b()
#define mark_depsan_atomic_long_or_b()

/* Value-returning atomics */

#define mark_depsan_atomic_fetch_add_b()
#define mark_depsan_atomic_xadd_b()
#define mark_depsan_atomic_fetch_add_relaxed_b()
#define mark_depsan_atomic_fetch_add_acquire_b()
#define mark_depsan_atomic_fetch_add_release_b()

#define mark_depsan_atomic_long_fetch_add_b()
#define mark_depsan_atomic_long_fetch_add_relaxed_b()
#define mark_depsan_atomic_long_fetch_add_acquire_b()
#define mark_depsan_atomic_long_fetch_add_release_b()

#define mark_depsan_atomic_fetch_inc_b()
#define mark_depsan_atomic_fetch_inc_relaxed_b()
#define mark_depsan_atomic_fetch_inc_acquire_b()
#define mark_depsan_atomic_fetch_inc_release_b()

#define mark_depsan_atomic_long_fetch_inc_b()
#define mark_depsan_atomic_long_fetch_inc_relaxed_b()
#define mark_depsan_atomic_long_fetch_inc_acquire_b()
#define mark_depsan_atomic_long_fetch_inc_release_b()

#define mark_depsan_atomic_fetch_sub_b()
#define mark_depsan_atomic_fetch_sub_relaxed_b()
#define mark_depsan_atomic_fetch_sub_acquire_b()
#define mark_depsan_atomic_fetch_sub_release_b()

#define mark_depsan_atomic_long_fetch_sub_b()
#define mark_depsan_atomic_long_fetch_sub_relaxed_b()
#define mark_depsan_atomic_long_fetch_sub_acquire_b()
#define mark_depsan_atomic_long_fetch_sub_release_b()

#define mark_depsan_atomic_fetch_dec_b()
#define mark_depsan_atomic_fetch_dec_relaxed_b()
#define mark_depsan_atomic_fetch_dec_acquire_b()
#define mark_depsan_atomic_fetch_dec_release_b()

#define mark_depsan_atomic_long_fetch_dec_b()
#define mark_depsan_atomic_long_fetch_dec_relaxed_b()
#define mark_depsan_atomic_long_fetch_dec_acquire_b()
#define mark_depsan_atomic_long_fetch_dec_release_b()

#define mark_depsan_atomic_fetch_and_b()
#define mark_depsan_atomic_fetch_and_relaxed_b()
#define mark_depsan_atomic_fetch_and_acquire_b()
#define mark_depsan_atomic_fetch_and_release_b()

#define mark_depsan_atomic_long_fetch_and_b()
#define mark_depsan_atomic_long_fetch_and_relaxed_b()
#define mark_depsan_atomic_long_fetch_and_acquire_b()
#define mark_depsan_atomic_long_fetch_and_release_b()

#define mark_depsan_atomic_fetch_andnot_b()
#define mark_depsan_atomic_fetch_andnot_relaxed_b()
#define mark_depsan_atomic_fetch_andnot_acquire_b()
#define mark_depsan_atomic_fetch_andnot_release_b()

#define mark_depsan_atomic_long_fetch_andnot_b()
#define mark_depsan_atomic_long_fetch_andnot_relaxed_b()
#define mark_depsan_atomic_long_fetch_andnot_acquire_b()
#define mark_depsan_atomic_long_fetch_andnot_release_b()

#define mark_depsan_atomic_fetch_or_b()
#define mark_depsan_atomic_fetch_or_relaxed_b()
#define mark_depsan_atomic_fetch_or_acquire_b()
#define mark_depsan_atomic_fetch_or_release_b()

#define mark_depsan_atomic_long_fetch_or_b()
#define mark_depsan_atomic_long_fetch_or_relaxed_b()
#define mark_depsan_atomic_long_fetch_or_acquire_b()
#define mark_depsan_atomic_long_fetch_or_release_b()

#define mark_depsan_atomic_add_return_b()
#define mark_depsan_atomic_add_return_relaxed_b()
#define mark_depsan_atomic_add_return_acquire_b()
#define mark_depsan_atomic_add_return_release_b()

#define mark_depsan_atomic_inc_return_b()
#define mark_depsan_atomic_inc_return_relaxed_b()
#define mark_depsan_atomic_inc_return_acquire_b()
#define mark_depsan_atomic_inc_return_release_b()

#define mark_depsan_atomic_long_inc_return_b()
#define mark_depsan_atomic_long_inc_return_relaxed_b()
#define mark_depsan_atomic_long_inc_return_acquire_b()
#define mark_depsan_atomic_long_inc_return_release_b()

#define mark_depsan_atomic_sub_return_b()
#define mark_depsan_atomic_sub_return_relaxed_b()
#define mark_depsan_atomic_sub_return_acquire_b()
#define mark_depsan_atomic_sub_return_release_b()

#define mark_depsan_atomic_long_sub_return_b()
#define mark_depsan_atomic_long_sub_return_relaxed_b()
#define mark_depsan_atomic_long_sub_return_acquire_b()
#define mark_depsan_atomic_long_sub_return_release_b()

#define mark_depsan_atomic_dec_return_b()
#define mark_depsan_atomic_dec_return_relaxed_b()
#define mark_depsan_atomic_dec_return_acquire_b()
#define mark_depsan_atomic_dec_return_release_b()

#define mark_depsan_atomic_long_dec_return_b()
#define mark_depsan_atomic_long_dec_return_relaxed_b()
#define mark_depsan_atomic_long_dec_return_acquire_b()
#define mark_depsan_atomic_long_dec_return_release_b()

#define mark_depsan_atomic_xchg_b()
#define mark_depsan_atomic_xchg_relaxed_b()
#define mark_depsan_atomic_xchg_release_b()
#define mark_depsan_atomic_xchg_acquire_b()

#define mark_depsan_atomic_long_xchg_b()
#define mark_depsan_atomic_long_xchg_relaxed_b()
#define mark_depsan_atomic_long_xchg_release_b()
#define mark_depsan_atomic_long_xchg_acquire_b()

#define mark_depsan_atomic_cmpxchg_b()
#define mark_depsan_atomic_cmpxchg_relaxed_b()
#define mark_depsan_atomic_cmpxchg_acquire_b()
#define mark_depsan_atomic_cmpxchg_release_b()

#define mark_depsan_atomic_long_cmpxchg_b()
#define mark_depsan_atomic_long_cmpxchg_relaxed_b()
#define mark_depsan_atomic_long_cmpxchg_acquire_b()
#define mark_depsan_atomic_long_cmpxchg_release_b()

#define mark_depsan_atomic_sub_and_test_b()
#define mark_depsan_atomic_dec_and_test_b()
#define mark_depsan_atomic_inc_and_test_b()
#define mark_depsan_atomic_add_negative_b()

#define mark_depsan_atomic_long_sub_and_test_b()
#define mark_depsan_atomic_long_dec_and_test_b()
#define mark_depsan_atomic_long_inc_and_test_b()
#define mark_depsan_atomic_long_add_negative_b()

/** End **/
/* Basic operations */
#define mark_depsan_atomic_read_e()
#define mark_depsan_atomic_set_e()
#define mark_depsan_atomic_read_acquire_e()
#define mark_depsan_atomic_set_release_e()

#define mark_depsan_atomic_long_read_e()
#define mark_depsan_atomic_long_set_e()
#define mark_depsan_atomic_long_read_acquire_e()
#define mark_depsan_atomic_long_set_release_e()

/* Non-value-returning atomics */
#define mark_depsan_atomic_add_e()
#define mark_depsan_atomic_sub_e()
#define mark_depsan_atomic_inc_e()
#define mark_depsan_atomic_dec_e()
#define mark_depsan_atomic_and_e()
#define mark_depsan_atomic_andnot_e()
#define mark_depsan_atomic_or_e()

#define mark_depsan_atomic_long_add_e()
#define mark_depsan_atomic_long_sub_e()
#define mark_depsan_atomic_long_inc_e()
#define mark_depsan_atomic_long_dec_e()
#define mark_depsan_atomic_long_and_e()
#define mark_depsan_atomic_long_andnot_e()
#define mark_depsan_atomic_long_or_e()

/* Value-returning atomics */

#define mark_depsan_atomic_fetch_add_e()
#define mark_depsan_atomic_xadd_e()
#define mark_depsan_atomic_fetch_add_relaxed_e()
#define mark_depsan_atomic_fetch_add_acquire_e()
#define mark_depsan_atomic_fetch_add_release_e()

#define mark_depsan_atomic_long_fetch_add_e()
#define mark_depsan_atomic_long_fetch_add_relaxed_e()
#define mark_depsan_atomic_long_fetch_add_acquire_e()
#define mark_depsan_atomic_long_fetch_add_release_e()

#define mark_depsan_atomic_fetch_inc_e()
#define mark_depsan_atomic_fetch_inc_relaxed_e()
#define mark_depsan_atomic_fetch_inc_acquire_e()
#define mark_depsan_atomic_fetch_inc_release_e()

#define mark_depsan_atomic_long_fetch_inc_e()
#define mark_depsan_atomic_long_fetch_inc_relaxed_e()
#define mark_depsan_atomic_long_fetch_inc_acquire_e()
#define mark_depsan_atomic_long_fetch_inc_release_e()

#define mark_depsan_atomic_fetch_sub_e()
#define mark_depsan_atomic_fetch_sub_relaxed_e()
#define mark_depsan_atomic_fetch_sub_acquire_e()
#define mark_depsan_atomic_fetch_sub_release_e()

#define mark_depsan_atomic_long_fetch_sub_e()
#define mark_depsan_atomic_long_fetch_sub_relaxed_e()
#define mark_depsan_atomic_long_fetch_sub_acquire_e()
#define mark_depsan_atomic_long_fetch_sub_release_e()

#define mark_depsan_atomic_fetch_dec_e()
#define mark_depsan_atomic_fetch_dec_relaxed_e()
#define mark_depsan_atomic_fetch_dec_acquire_e()
#define mark_depsan_atomic_fetch_dec_release_e()

#define mark_depsan_atomic_long_fetch_dec_e()
#define mark_depsan_atomic_long_fetch_dec_relaxed_e()
#define mark_depsan_atomic_long_fetch_dec_acquire_e()
#define mark_depsan_atomic_long_fetch_dec_release_e()

#define mark_depsan_atomic_fetch_and_e()
#define mark_depsan_atomic_fetch_and_relaxed_e()
#define mark_depsan_atomic_fetch_and_acquire_e()
#define mark_depsan_atomic_fetch_and_release_e()

#define mark_depsan_atomic_long_fetch_and_e()
#define mark_depsan_atomic_long_fetch_and_relaxed_e()
#define mark_depsan_atomic_long_fetch_and_acquire_e()
#define mark_depsan_atomic_long_fetch_and_release_e()

#define mark_depsan_atomic_fetch_andnot_e()
#define mark_depsan_atomic_fetch_andnot_relaxed_e()
#define mark_depsan_atomic_fetch_andnot_acquire_e()
#define mark_depsan_atomic_fetch_andnot_release_e()

#define mark_depsan_atomic_long_fetch_andnot_e()
#define mark_depsan_atomic_long_fetch_andnot_relaxed_e()
#define mark_depsan_atomic_long_fetch_andnot_acquire_e()
#define mark_depsan_atomic_long_fetch_andnot_release_e()

#define mark_depsan_atomic_fetch_or_e()
#define mark_depsan_atomic_fetch_or_relaxed_e()
#define mark_depsan_atomic_fetch_or_acquire_e()
#define mark_depsan_atomic_fetch_or_release_e()

#define mark_depsan_atomic_long_fetch_or_e()
#define mark_depsan_atomic_long_fetch_or_relaxed_e()
#define mark_depsan_atomic_long_fetch_or_acquire_e()
#define mark_depsan_atomic_long_fetch_or_release_e()

#define mark_depsan_atomic_add_return_e()
#define mark_depsan_atomic_add_return_relaxed_e()
#define mark_depsan_atomic_add_return_acquire_e()
#define mark_depsan_atomic_add_return_release_e()

#define mark_depsan_atomic_inc_return_e()
#define mark_depsan_atomic_inc_return_relaxed_e()
#define mark_depsan_atomic_inc_return_acquire_e()
#define mark_depsan_atomic_inc_return_release_e()

#define mark_depsan_atomic_long_inc_return_e()
#define mark_depsan_atomic_long_inc_return_relaxed_e()
#define mark_depsan_atomic_long_inc_return_acquire_e()
#define mark_depsan_atomic_long_inc_return_release_e()

#define mark_depsan_atomic_sub_return_e()
#define mark_depsan_atomic_sub_return_relaxed_e()
#define mark_depsan_atomic_sub_return_acquire_e()
#define mark_depsan_atomic_sub_return_release_e()

#define mark_depsan_atomic_long_sub_return_e()
#define mark_depsan_atomic_long_sub_return_relaxed_e()
#define mark_depsan_atomic_long_sub_return_acquire_e()
#define mark_depsan_atomic_long_sub_return_release_e()

#define mark_depsan_atomic_dec_return_e()
#define mark_depsan_atomic_dec_return_relaxed_e()
#define mark_depsan_atomic_dec_return_acquire_e()
#define mark_depsan_atomic_dec_return_release_e()

#define mark_depsan_atomic_long_dec_return_e()
#define mark_depsan_atomic_long_dec_return_relaxed_e()
#define mark_depsan_atomic_long_dec_return_acquire_e()
#define mark_depsan_atomic_long_dec_return_release_e()

#define mark_depsan_atomic_xchg_e()
#define mark_depsan_atomic_xchg_relaxed_e()
#define mark_depsan_atomic_xchg_release_e()
#define mark_depsan_atomic_xchg_acquire_e()

#define mark_depsan_atomic_long_xchg_e()
#define mark_depsan_atomic_long_xchg_relaxed_e()
#define mark_depsan_atomic_long_xchg_release_e()
#define mark_depsan_atomic_long_xchg_acquire_e()

#define mark_depsan_atomic_cmpxchg_e()
#define mark_depsan_atomic_cmpxchg_relaxed_e()
#define mark_depsan_atomic_cmpxchg_acquire_e()
#define mark_depsan_atomic_cmpxchg_release_e()

#define mark_depsan_atomic_long_cmpxchg_e()
#define mark_depsan_atomic_long_cmpxchg_relaxed_e()
#define mark_depsan_atomic_long_cmpxchg_acquire_e()
#define mark_depsan_atomic_long_cmpxchg_release_e()

#define mark_depsan_atomic_sub_and_test_e()
#define mark_depsan_atomic_dec_and_test_e()
#define mark_depsan_atomic_inc_and_test_e()
#define mark_depsan_atomic_add_negative_e()

#define mark_depsan_atomic_long_sub_and_test_e()
#define mark_depsan_atomic_long_dec_and_test_e()
#define mark_depsan_atomic_long_inc_and_test_e()
#define mark_depsan_atomic_long_add_negative_e()

#endif /* CONFIG_DEPSAN */


#endif /* _LINUX_DEPSAN_CHECKS_H */
