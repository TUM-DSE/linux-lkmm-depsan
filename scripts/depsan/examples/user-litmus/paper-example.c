#include <pthread.h>
#include <assert.h>
#include "lkmm.h"

int x;
int y;

int r0, r1, r2;

spinlock_t s;

extern void foo();
extern void bar();

void *thread_1(void *unused)
{
	r1 = READ_ONCE(x);
	spin_lock(&s);
	spin_unlock(&s);
	spin_lock(&s);
	spin_unlock(&s);

	if (r1 == 0) {
	    WRITE_ONCE(y, 1);
	    foo();
	} else {
	    WRITE_ONCE(y, 1);
	    bar();
	}
	return NULL;
}

void *thread_2(void *unused)
{
	return NULL;
}

int main(void)
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, thread_1, NULL);
	pthread_create(&t2, NULL, thread_2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
