#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

struct vec {
    int *elems;
    int length;
    int capacity;
};

static void vec_free(struct vec *const vp)
{
    free(vp->elems);
    vp->elems = NULL;

    vp->length = vp->capacity = 0;
}

static inline int vec_length(const struct vec *const vp)
{
    return vp->length;
}

static void vec_detail_expand(struct vec *const vp)
{
    enum { initial_capacity = 1 };

    vp->capacity = (vp->capacity == 0 ? initial_capacity : vp->capacity * 2);
    vp->elems = xrealloc(vp->elems, vp->capacity * sizeof *vp->elems);
}

static inline void vec_push_back(struct vec *const vp, const int x)
{
    if (vp->length == vp->capacity) vec_detail_expand(vp);
    vp->elems[vp->length++] = x;
}

static inline int vec_get(const struct vec *const vp, const int i)
{
    return vp->elems[i];
}

struct graph {
    struct vec *adj;
    int vertex_count;
};

static struct graph graph_init(const int vertex_count)
{
    return (struct graph){xcalloc(vertex_count, sizeof(struct vec)),
                          vertex_count};
}

static void graph_free(struct graph *const gp)
{
    while (gp->vertex_count > 0) vec_free(&gp->adj[--gp->vertex_count]);

    free(gp->adj);
    gp->adj = NULL;
}

static inline void graph_add_edge(const struct graph *const gp,
                                  const int src, const int dest)
{
    vec_push_back(&gp->adj[src], dest);
}

// Visitation states for depth-first traversal of a directed graph.
enum color {
    k_color_white,  // unvisited (this enumerator must appear first)
    k_color_gray,   // visited but not yet fully explored
    k_color_black   // visited and fully explored
};

// Stack frame for iteratively implemented simulated recursive graph DFS.
struct frame {
    int vertex;
    int index;
};

// Stack for iteratively implemented simulated recursive graph DFS.
struct stack {
    struct frame *items;
    int size;
    int capacity;
};

static inline struct stack stack_init(void)
{
    return (struct stack){NULL, 0, 0};
}

static void stack_free(struct stack *const sp)
{
    free(sp->items);
    sp->items = NULL;

    sp->size = sp->capacity = 0;
}

static inline bool stack_empty(const struct stack *const sp)
{
    return sp->size == 0;
}

static void stack_detail_expand(struct stack *const sp)
{
    enum { initial_capacity = 1 };

    sp->capacity = (sp->capacity == 0 ? initial_capacity : sp->capacity * 2);
    sp->items = xrealloc(sp->items, sp->capacity * sizeof *sp->items);
}

static inline void stack_emplace(struct stack *const sp, const int vertex)
{
    if (sp->size == sp->capacity) stack_detail_expand(sp);

    struct frame *const fp = &sp->items[sp->size++];
    fp->vertex = vertex;
    fp->index = 0;
}

static inline struct frame *stack_top(const struct stack *const sp)
{
    return &sp->items[sp->size - 1];
}

static inline void stack_pop(struct stack *const sp)
{
    --sp->size;
}

static bool graph_detail_has_cycle(const struct graph *const gp,
                                   enum color *const vis,
                                   struct stack *const sp,
                                   int **const outp, const int start)
{
    if (vis[start] == k_color_black) return false;

    assert(vis[start] == k_color_white);
    vis[start] = k_color_gray;
    assert(stack_empty(sp));
    stack_emplace(sp, start);

    while (!stack_empty(sp)) {
        struct frame *const fp = stack_top(sp);
        const struct vec *const rowp = &gp->adj[fp->vertex];

        if (fp->index == vec_length(rowp)) {
            vis[fp->vertex] = k_color_black;
            *(*outp)++ = fp->vertex;
            stack_pop(sp);
            continue;
        }

        const int dest = vec_get(rowp, fp->index++);

        switch (vis[dest]) {
        case k_color_white:
            vis[dest] = k_color_gray;
            stack_emplace(sp, dest);
            continue;

        case k_color_gray:
            return true;

        case k_color_black:
            continue;
        }

        abort(); // only reached if a visitation state has an invalid value
    }

    return false;
}

static int *graph_reverse_topological_sort(const struct graph *const gp)
{
    int *ret = xcalloc(gp->vertex_count, sizeof *ret), *out = ret;
    enum color *vis = xcalloc(gp->vertex_count, sizeof *vis);
    struct stack s = stack_init();

    int start = 0;
    while (start < gp->vertex_count
            && !graph_detail_has_cycle(gp, vis, &s, &out, start))
        ++start;

    if (start < gp->vertex_count) {
        assert(out - ret < gp->vertex_count);
        free(ret);
        ret = out = NULL;
    } else {
        assert(out - ret == gp->vertex_count);
    }

    stack_free(&s);
    free(vis);
    vis = NULL;

    return ret;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findOrder(const int numCourses, int **const prerequisites,
               const int prerequisitesRowSize, int *const prerequisitesColSizes,
               int *const returnSize)
{
    const int vertex_count = numCourses; // courses are 0, ..., vertex_count - 1
    const int edge_count = prerequisitesRowSize; // the number of prerequisites
    (void)prerequisitesColSizes; // an edge_count-length sequence of all 2s

    struct graph g = graph_init(vertex_count);

    for (int i = 0; i < edge_count; ++i)
        graph_add_edge(&g, prerequisites[i][0], prerequisites[i][1]);

    int *const ret = graph_reverse_topological_sort(&g);

    graph_free(&g);

    *returnSize = (ret ? vertex_count : 0);
    return ret;
}

static void print_result(const int *const result, const int result_length)
{
    putchar('[');

    const char *sep = "";
    for (int i = 0; i < result_length; ++i) {
        printf("%s%d", sep, result[i]);
        sep = ", ";
    }

    puts("]");
}

static void test(const int vertex_count, int (*reverse_edges)[2],
                 int edge_count)
{
    int **prerequisites = xcalloc(edge_count, sizeof *prerequisites);
    for (int i = 0; i < edge_count; ++i) {
        prerequisites[i] = xcalloc(2, sizeof *prerequisites[i]);
        prerequisites[i][0] = reverse_edges[i][0];
        prerequisites[i][1] = reverse_edges[i][1];
    }

    int *prerequisitesColSizes = xcalloc(edge_count,
                                         sizeof *prerequisitesColSizes);
    for (int i = 0; i < edge_count; ++i) prerequisitesColSizes[i] = 2;

    int result_length = 0;
    int *result = findOrder(vertex_count, prerequisites, edge_count,
                            prerequisitesColSizes, &result_length);
    print_result(result, result_length);
    free(result);
    result = NULL;

    free(prerequisitesColSizes);
    prerequisitesColSizes = NULL;

    while (edge_count > 0) free(prerequisites[--edge_count]);
    free(prerequisites);
    prerequisites = NULL;
}

#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))

int main(void)
{
    int re1[][2] = {{1, 0}};
    test(2, re1, ARRAY_SIZE(re1));

    int re2[][2] = {{1, 0}, {0, 1}};
    test(2, re2, ARRAY_SIZE(re2));

    int re3[][2] = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    test(4, re3, ARRAY_SIZE(re3));

    int re4[][2] = {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {1, 2}};
    test(4, re4, ARRAY_SIZE(re4));

    int re5[][2] = {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {1, 2}, {0, 3}};
    test(4, re5, ARRAY_SIZE(re5));

    int re6[][2] = {{0, 1}, {1, 2}, {0, 3}, {3, 0}};
    test(4, re6, ARRAY_SIZE(re6));
}
