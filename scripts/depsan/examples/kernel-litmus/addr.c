#include "common.h"

MODULE_DESCRIPTION(
	"Kernel module containing address dependency litmus tests");
MODULE_LICENSE("GPL");

#ifndef _DEPSAN_ADDR_TEST
#define _DEPSAN_ADDR_TEST

static int x = 0;
static int y = 0;
static int z = 0;

static int *X = &x;

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

static noinline void ronce_sr(void)
{
	int r1;
	int *r2;
	int r3;

	r1 = READ_ONCE(x);

	r2 = &shared[r1];

	smp_store_release(r2,42);
}

static noinline void bug_ronce_mem_wonce(void)
{
	int migrate_nodes = 1;
	int head = 0;
	int list = 1;

	int *stable_node = READ_ONCE(X);
	*(stable_node + head) = z;
	WRITE_ONCE(*(stable_node + head), 1);
}

// ######################################################################### //
#include <linux/mm.h>
#include <linux/rbtree.h>

/**
 * struct ksm_stable_node - node of the stable rbtree
 * @node: rb node of this ksm page in the stable tree
 * @head: (overlaying parent) &migrate_nodes indicates temporarily on that list
 * @hlist_dup: linked into the stable_node->hlist with a stable_node chain
 * @list: linked into migrate_nodes, pending placement in the proper node tree
 * @hlist: hlist head of rmap_items using this ksm page
 * @kpfn: page frame number of this ksm page (perhaps temporarily on wrong nid)
 * @chain_prune_time: time of the last full garbage collection
 * @rmap_hlist_len: number of rmap_item entries in hlist or STABLE_NODE_CHAIN
 * @nid: NUMA node id of stable tree in which linked (may not match kpfn)
 */
struct ksm_stable_node {
	union {
		struct rb_node node;	/* when node of stable tree */
		struct {		/* when listed for migration */
			struct list_head *head;
			struct {
				struct hlist_node hlist_dup;
				struct list_head list;
			};
		};
	};
	struct hlist_head hlist;
	union {
		unsigned long kpfn;
		unsigned long chain_prune_time;
	};
	/*
	 * STABLE_NODE_CHAIN can be any negative number in
	 * rmap_hlist_len negative range, but better not -1 to be able
	 * to reliably detect underflows.
	 */
#define STABLE_NODE_CHAIN -1024
	int rmap_hlist_len;
#ifdef CONFIG_NUMA
	int nid;
#endif
};
static inline void *folio_raw_mapping(const struct folio *folio)
{
	unsigned long mapping = (unsigned long)folio->mapping;

	return (void *)(mapping & ~FOLIO_MAPPING_FLAGS);
}
static inline
struct ksm_stable_node *folio_stable_node(const struct folio *folio)
{
	return folio_test_ksm(folio) ? folio_raw_mapping(folio) : NULL;
}
static inline struct ksm_stable_node *page_stable_node(struct page *page)
{
	return folio_stable_node(page_folio(page));
}

static noinline void mm_ksm(void)
{
	struct ksm_stable_node *stable_node;
	stable_node = page_stable_node(page);
}

int all_addr_tests(void)
{

	ronce_ronce();
	ronce_sr();
	bug_ronce_mem_wonce();
	mm_ksm();
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
