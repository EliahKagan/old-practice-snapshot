static inline void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

static int compare(const void *const p, const void *const q)
{
    const int lhs = *(const int *)p;
    const int rhs = *(const int *)q;

    if (lhs < rhs) return -1;
    if (lhs > rhs) return +1;
    return 0;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *const numbers, const int numbersSize, const int target,
            int *const returnSize)
{
    int *const ret = xcalloc(2, sizeof *ret);
    *returnSize = 2;

    for (int left = 0; left < numbersSize - 1; ++left) {
        const int key = target - numbers[left];
        if (key < numbers[left]) break;

        void *const start = numbers + left + 1;
        const size_t count = numbersSize - left - 1;
        int *const pos = bsearch(&key, start, count, sizeof *numbers, compare);

        if (pos) {
            ret[0] = left + 1;
            ret[1] = pos - numbers + 1;
            break;
        }
    }

    return ret;
}
