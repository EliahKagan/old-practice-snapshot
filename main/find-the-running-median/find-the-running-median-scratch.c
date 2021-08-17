#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void *xmalloc(const size_t n)
{
    void *const p = malloc(n);
    if (p == NULL) abort();
    return p;
}

static void *xrealloc(void *const p, const ptrdiff_t n)
{
    void *const q = realloc(p, n);
    if (q == NULL) abort();
    return q;
}

enum { k_initial_capacity = 256 };
static_assert(k_initial_capacity > 0, "nonpositive initial capacity!");

struct minheap {
    ptrdiff_t capacity, length;
    int elems[];
};

static void minheap_detail_grow(struct minheap *const minhp)
{
    assert(minhp->capacity >= k_initial_capacity);
    minhp->capacity *= 2;
    minhp = xrealloc(minhp, sizeof(*minhp) + (size_t)minhp->capacity * sizeof minhp->elems[0]);
}

static struct minheap *minheap_create()
{
    struct minheap *const minhp =
            xmalloc(sizeof(*minhp)
                    + k_initial_capacity * sizeof minhp->elems[0]);

    minhp->capacity = k_initial_capacity;
    minhp->length = 0;
    return minhp;
}



struct maxheap {
    struct minheap *heap_ptr;
};

int main()
{
    struct maxheap heap;
}
