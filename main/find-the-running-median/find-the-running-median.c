#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void *xrealloc(void *const p, const size_t n)
{
    void *const q = realloc(p, n);
    if (q == NULL) abort();
    return q;
}

typedef int Element;
enum { k_initial_capacity = 256 };
static_assert(k_initial_capacity > 0, "nonpositive initial capacity!");

struct minheap {
    ptrdiff_t capacity, length;
    Element *elems;
};

static void minheap_detail_allocate(struct minheap *const minhp)
{
    assert(minhp->capacity >= k_initial_capacity);

    minhp->elems = xrealloc(minhp->elems,
                            (size_t)minhp->capacity * sizeof *minhp->elems);
}

static inline void minheap_detail_grow(struct minheap *const minhp)
{
    minhp->capacity *= 2;
    minheap_detail_allocate(minhp);
}

static inline void minheap_detail_swap(const struct minheap *const minhp,
                                       const ptrdiff_t i, const ptrdiff_t j)
{
    const Element tmp = minhp->elems[i];
    minhp->elems[i] = minhp->elems[j];
    minhp->elems[j] = tmp;
}

static void minheap_detail_heapify_down(const struct minheap *const minhp)
{
    for (ptrdiff_t current_index = 0; ; ) {
        const ptrdiff_t left_child_index = current_index * 2 + 1;
        if (left_child_index >= minhp->length) break;

        const ptrdiff_t right_child_index = left_child_index + 1;
        const ptrdiff_t child_index =
                (right_child_index < minhp->length
                            && minhp->elems[right_child_index]
                             < minhp->elems[left_child_index]
                    ? right_child_index
                    : left_child_index);

        if (minhp->elems[current_index] <= minhp->elems[child_index]) break;
        minheap_detail_swap(minhp, current_index, child_index);
        current_index = child_index;
    }
}

static void minheap_detail_heapify_up(const struct minheap *const minhp)
{
    for (ptrdiff_t current_index = minhp->length - 1; current_index != 0; ) {
        const ptrdiff_t parent_index = (current_index - 1) / 2;
        if (minhp->elems[parent_index] <= minhp->elems[current_index]) break;
        minheap_detail_swap(minhp, current_index, parent_index);
        current_index = parent_index;
    }
}

static struct minheap minheap_create(void)
{
    struct minheap minh = { k_initial_capacity, 0, NULL };
    minheap_detail_allocate(&minh);
    return minh;
}

static void minheap_destroy(struct minheap *const minhp)
{
    free(minhp->elems);
    minhp->elems = NULL;
    minhp->length = minhp->capacity = 0;
}

static inline ptrdiff_t minheap_length(const struct minheap *const minhp)
{
    return minhp->length;
}

static inline Element minheap_peek(const struct minheap *const minhp)
{
    return minhp->elems[0];
}

static Element minheap_pop(struct minheap *const minhp)
{
    const Element value = minhp->elems[0];
    minhp->elems[0] = minhp->elems[--minhp->length];
    minheap_detail_heapify_down(minhp);
    return value;
}

static void minheap_push(struct minheap *const minhp, const Element value)
{
    if (minhp->length == minhp->capacity) minheap_detail_grow(minhp);
    minhp->elems[minhp->length++] = value;
    minheap_detail_heapify_up(minhp);
}

struct maxheap {
    struct minheap heap;
};

static inline struct maxheap maxheap_create(void)
{
    return (struct maxheap) { minheap_create() };
}

static inline void maxheap_destroy(struct maxheap *const maxhp)
{
    minheap_destroy(&maxhp->heap);
}

static inline ptrdiff_t maxheap_length(const struct maxheap *const maxhp)
{
    return minheap_length(&maxhp->heap);
}

static inline Element maxheap_peek(const struct maxheap *const maxhp)
{
    return -minheap_peek(&maxhp->heap);
}

static inline Element maxheap_pop(struct maxheap *const maxhp)
{
    return -minheap_pop(&maxhp->heap);
}

static inline void maxheap_push(struct maxheap *const maxhp,
                                const Element value)
{
    minheap_push(&maxhp->heap, -value);
}

static void add(struct maxheap *const lowp, struct minheap *const highp,
                const int e)
{
    if (e < maxheap_peek(lowp)) maxheap_push(lowp, e);
    else                        minheap_push(highp, e);
}

static void rebalance(struct maxheap *const lowp, struct minheap *const highp)
{
    switch (maxheap_length(lowp) - minheap_length(highp)) {
        case +2:    minheap_push(highp, maxheap_pop(lowp));     break;
        case -2:    maxheap_push(lowp, minheap_pop(highp));     break;
        default:    break;  // they cannot currently be made any more balanced
    }
}

static double compute_median(const struct maxheap *const lowp,
                             const struct minheap *const highp)
{
    const ptrdiff_t d = maxheap_length(lowp) - minheap_length(highp);

    return d == 0 ? (double)(maxheap_peek(lowp) + minheap_peek(highp)) / 2.0
                  : (double)(d > 0 ? maxheap_peek(lowp) : minheap_peek(highp));
}

static inline void put(const double x)
{
    printf("%.1f\n", x);
}

static inline int get()
{
    int e = 0;
    (void)scanf("%d", &e);
    return e;
}

int main(void)
{
    struct maxheap low = maxheap_create();
    struct minheap high = minheap_create();
    
    int n = get();

    maxheap_push(&low, get());
    put(maxheap_peek(&low));

    while (--n > 0) {
        add(&low, &high, get());
        rebalance(&low, &high);
        put(compute_median(&low, &high));
    }

    minheap_destroy(&high);
    maxheap_destroy(&low);
}
