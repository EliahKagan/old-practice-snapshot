#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

static inline void *xrealloc(void *const p, const size_t n)
{
    void *const ret = realloc(p, n);
    if (!ret && n) abort();
    return ret;
}

static inline int (min)(const int x, const int y)
{
    return y < x ? y : x;
}

struct vec {
    int *elems;
    int length;
    int capacity;
};

static inline struct vec vec_init(void)
{
    return (struct vec){NULL, 0, 0};
}

static void vec_free(struct vec *const vp)
{
    free(vp->elems);
    vp->elems = NULL;

    vp->length = vp->capacity = 0;
}

static void vec_detail_expand(struct vec *const vp)
{
    enum { initial_capacity = 1 };

    vp->capacity = (vp->capacity == 0 ? initial_capacity : vp->capacity * 2);
    vp->elems = xrealloc(vp->elems, vp->capacity);
}

static inline void vec_push_back(struct vec *const vp, const int x)
{
    if (vp->length == vp->capacity) vec_detail_expand(vp);
    vp->elems[vp->length++] = x;
}

static inline int *vec_begin(const struct vec *const vp)
{
    return vp->elems;
}

static inline int *vec_end(const struct vec *const vp)
{
    return vp->elems + vp->length;
}

struct graph {
    struct vec *adj;
    int vertex_count;
};

static struct graph graph_read(void)
{
    struct graph g = {NULL, 0};
    (void)scanf("%d", &g.vertex_count);
    g.adj = xcalloc(g.vertex_count + 1, sizeof *g.adj); // 1-based indexing

    int edge_count = 0, u = 0, v = 0;
    for ((void)scanf("%d", &edge_count); edge_count > 0; --edge_count) {
        (void)scanf("%d%d", &u, &v);
        vec_push_back(&g.adj[u], v);
        vec_push_back(&g.adj[v], u);
    }

    return g;
}

static void graph_free(struct graph *const gp)
{
    while (gp->vertex_count > 0) vec_free(&gp->adj[--gp->vertex_count]);

    free(gp->adj);
    gp->adj = NULL;
}

static inline int *graph_row_begin(const struct graph *const gp, const int src)
{
    return vec_begin(&gp->adj[src]);
}

static inline int *graph_row_end(const struct graph *const gp, const int src)
{
    return vec_end(&gp->adj[src]);
}

struct queue {
    int *elems;
    int start;
    int length;
    int capacity;
};

static inline struct queue queue_init(void)
{
    return (struct queue){NULL, 0, 0, 0, 0};
}

static void queue_free(struct queue *const qp)
{
    free(qp->elems);
    qp->elems = NULL;

    qp->start = qp->length = qp->capacity = 0;
}

static inline int queue_length(const struct queue *const qp)
{
    return qp->length;
}

static void queue_detail_expand(struct queue *const qp)
{
    enum { initial_capacity = 1 };

    const int new_capacity = (qp->capacity == 0 ? initial_capacity
                                                : qp->capacity * 2);

    int *const new_elems = xcalloc(new_capacity, sizeof *new_elems);

    const int pre_wrap = (min)(qp->length, qp->capacity - qp->start);
    memcpy(new_elems, qp->elems + qp->start, pre_wrap * sizeof *qp->elems);
    const int post_wrap = qp->length - pre_wrap;
    memcpy(new_elems + pre_wrap, qp->elems, post_wrap * sizeof *qp->elems);

    free(qp->elems);
    qp->elems = new_elems;
    qp->start = 0;
    qp->capacity = new_capacity;
}

static inline void queue_enqueue(struct queue *const qp, const int x)
{
    if (qp->length == qp->capacity) queue_detail_expand(qp);

    const int index = (qp->start + qp->length++) % qp->capacity;
    qp->elems[index] = x;
}

static inline int queue_dequeue(struct queue *const qp)
{
    const int ret = qp->elems[qp->start++];
    qp->start %= qp->capacity;
    --qp->length;
    return ret;
}

int main(void)
{
    //
}
