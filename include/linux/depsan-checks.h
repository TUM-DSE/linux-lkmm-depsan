/* SPDX-License-Identifier: GPL-2.0 */
/*
 */

#ifndef _LINUX_DEPSAN_CHECKS_H
#define _LINUX_DEPSAN_CHECKS_H

/* Note: Only include what is already included by compiler.h. */
#include <linux/compiler_attributes.h>
#include <linux/types.h>

static inline void __depsan_mb_b(void)			{ }
static inline void __depsan_mb_e(void)			{ }
static inline void __depsan_wmb_b(void)			{ }
static inline void __depsan_wmb_e(void)			{ }
static inline void __depsan_rmb_b(void)			{ }
static inline void __depsan_rmb_e(void)			{ }
static inline void __depsan_release_b(void)		{ }
static inline void __depsan_release_e(void)		{ }
static inline void __depsan_acquire_b(void)		{ }
static inline void __depsan_acquire_e(void)		{ }
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

#ifdef CONFIG_DEPSAN

#define mark_depsan_mb_b()		__depsan_mb_b()
#define mark_depsan_mb_e()		__depsan_mb_e()
#define mark_depsan_wmb_b()		__depsan_wmb_b()
#define mark_depsan_wmb_e()		__depsan_wmb_e()
#define mark_depsan_rmb_b()		__depsan_rmb_b()
#define mark_depsan_rmb_e()		__depsan_rmb_e()
#define mark_depsan_release_b()		__depsan_release_b()
#define mark_depsan_release_e()		__depsan_release_e()
#define mark_depsan_acquire_b()		__depsan_acquire_b()
#define mark_depsan_acquire_e()		__depsan_acquire_e()
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

#else /* CONFIG_DEPSAN */

#define mark_depsan_mb_b()
#define mark_depsan_mb_e()
#define mark_depsan_wmb_b()
#define mark_depsan_wmb_e()
#define mark_depsan_rmb_b()
#define mark_depsan_rmb_e()
#define mark_depsan_release_b()
#define mark_depsan_release_e()
#define mark_depsan_acquire_b()
#define mark_depsan_acquire_e()
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

#endif /* CONFIG_DEPSAN */


#endif /* _LINUX_DEPSAN_CHECKS_H */
