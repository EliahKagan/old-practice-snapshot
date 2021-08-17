static void *xmalloc(const size_t len)
{
    void *const p = malloc(len);
    if (p == NULL) abort();
    return p;
}

static void *xrealloc(void *const p, const size_t len)
{
    void *const q = realloc(p, len);
    if (q == NULL) abort();
    return q;
}

struct quad_vec {
    size_t capacity, length;
    int *restrict *restrict elems;
};

static void quad_vec_detail_grow(struct quad_vec *const qvp)
{
    qvp->capacity *= 2u;
    qvp->elems = xrealloc(qvp->elems, sizeof(int *) * qvp->capacity);
}

static inline int *quad_vec_detail_make_element(const int w, const int x,
                                                const int y, const int z)
{
    int *const p = xmalloc(sizeof *p * 4);

    p[0] = w;
    p[1] = x;
    p[2] = y;
    p[3] = z;

    return p;
}

static inline struct quad_vec quad_vec_create()
{
    enum { initial_capacity = 1 };

    return (struct quad_vec) {
        .capacity = initial_capacity,
        .length = 0u,
        .elems = xmalloc(sizeof(int *) * initial_capacity)
    };
}

static inline size_t quad_vec_length(const struct quad_vec *const qvp)
{
    return qvp->length;
}

static inline int **quad_vec_data(const struct quad_vec *const qvp)
{
    return qvp->elems;
}

static inline void quad_vec_push_back(struct quad_vec *const qvp, const int w,
                                      const int x, const int y, const int z)
{
    if (qvp->length == qvp->capacity) quad_vec_detail_grow(qvp);
    qvp->elems[qvp->length++] = quad_vec_detail_make_element(w, x, y, z);
}

static int cmp(const void *const lhsp, const void *const rhsp)
{
    const int lhs = *(const int *)lhsp, rhs = *(const int *)rhsp;

    if (lhs < rhs) return -1;
    if (lhs == rhs) return 0;
    return 1;
}

/**
* Return an array of arrays of size *returnSize.
* Note: The returned array must be malloced, assume caller calls free().
*/
int** fourSum(int *restrict const nums, const int numsSize, const int target,
              int *restrict const returnSize)
{
    struct quad_vec qv = quad_vec_create();
    if (numsSize < 4) goto done;

    qsort(nums, (size_t)numsSize, sizeof *nums, cmp);
    const int *const wq = nums + (numsSize - 3);
    const int *const xq = nums + (numsSize - 2);

    for (const int *wp = nums; wp != wq; ) {
        const int w = *wp, xyz_target = target - w;

        for (const int *xp = wp + 1; xp != xq; ) {
            const int x = *xp, yz_target = xyz_target - x;

            for (const int *yp = xp + 1, *zp = nums + (numsSize - 1);
                    yp < zp; ) {
                const int y = *yp, z = *zp, yz_sum = y + z;

                if (yz_sum == yz_target) quad_vec_push_back(&qv, w, x, y, z);

                if (yz_sum <= yz_target)
                    while (*yp == y && yp < zp) ++yp;

                if (yz_sum >= yz_target)
                    while (*zp == z && yp < zp) --zp;
            }

            while (*xp == x && xp != xq) ++xp;
        }

        while (*wp == w && wp != wq) ++wp;
    }

done:
    *returnSize = (int)quad_vec_length(&qv);
    return quad_vec_data(&qv);
}
