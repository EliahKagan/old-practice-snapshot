#ifdef NDEBUG
#error Assertions unexpectedly disabled.
#endif

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

struct DisjointSets {
    int *elems; // elems[i] holds the parent or negative size of i
    int count;
};

static void ds_init(struct DisjointSets *const dsp, const int element_count)
{
    assert(dsp);
    assert(element_count > 0);

    dsp->elems = xcalloc(element_count, sizeof *dsp->elems);
    dsp->count = element_count;

    for (int elem = 0; elem < dsp->count; ++elem) dsp->elems[elem] = -1;
}

static void ds_free(struct DisjointSets *const dsp)
{
    assert(dsp);

    free(dsp->elems);
    dsp->elems = NULL;
}

static inline bool ds_detail_exists(const struct DisjointSets *const dsp,
                                    const int elem)
{
    assert(dsp);
    return 0 <= elem && elem < dsp->count;
}

static int ds_detail_find_set(const struct DisjointSets *const dsp, int elem)
{
    assert(dsp);

    // Find the ancestor.
    int leader = elem;
    while (dsp->elems[leader] >= 0) leader = dsp->elems[leader];

    // Compress the path.
    while (elem != leader) {
        const int parent = dsp->elems[elem];
        dsp->elems[elem] = leader;
        elem = parent;
    }

    return leader;
}

static void ds_detail_join(const struct DisjointSets *const dsp,
                           const int parent, const int child)
{
    assert(dsp);

    dsp->elems[parent] += dsp->elems[child];
    dsp->elems[child] = parent;
}

static void ds_union(const struct DisjointSets *const dsp,
                     int elem1, int elem2)
{
    assert(dsp);
    assert(ds_detail_exists(dsp, elem1) && ds_detail_exists(dsp, elem2));

    // Find the ancestors and stop if they are the same.
    elem1 = ds_detail_find_set(dsp, elem1);
    elem2 = ds_detail_find_set(dsp, elem2);
    if (elem1 == elem2) return;

    // Union by (negatively stored) size.
    if (dsp->elems[elem2] < dsp->elems[elem1]) {
        ds_detail_join(dsp, elem2, elem1);
    } else {
        ds_detail_join(dsp, elem1, elem2);
    }
}

static int ds_size(const struct DisjointSets *const dsp, int elem)
{
    assert(dsp);
    assert(ds_detail_exists(dsp, elem));

    elem = ds_detail_find_set(dsp, elem);
    return -dsp->elems[elem];
}

static void run_queries(const struct DisjointSets *const dsp, int query_count)
{
    assert(dsp);
    assert(query_count > 0);

    while (query_count-- > 0) {
        char action = '\0';
        (void)scanf(" %c", &action);
        assert(action == 'M' || action == 'Q');

        if (action == 'M') {
            // Merge communities.
            int elem1 = 0, elem2 = 0;
            (void)scanf(" %d %d", &elem1, &elem2);
            assert(elem1 > 0 && elem2 > 0);
            ds_union(dsp, elem1, elem2);
        } else {
            // Query size.
            int elem = 0;
            (void)scanf(" %d", &elem);
            assert(elem > 0);
            printf("%d\n", ds_size(dsp, elem));
        }
    }
}

int main(void)
{
    int person_count = 0, query_count = 0;
    (void)scanf(" %d %d", &person_count, &query_count);
    assert(person_count > 0 && query_count > 0);

    struct DisjointSets ds = { 0 };
    ds_init(&ds, person_count + 1); // +1 for 1-based indexing
    run_queries(&ds, query_count);
    ds_free(&ds);
}
