static inline void swap(int *const p, int *const q)
{
    const int tmp = *p;
    *p = *q;
    *q = tmp;
}

static inline void reverse(int *first, int *last)
{
    while (first < last) swap(first++, --last);
}

static bool do_next_permutation(int *const first, int *const last)
{
    if (last - first < 2) return false;

    int *left = last - 2;
    for (; *left >= *(left + 1); --left)
        if (left == first) return false;

    int *right = last - 1;
    while (*left >= *right) --right;

    swap(left, right);
    reverse(left + 1, last);
    return true;
}

void nextPermutation(int *const nums, const int numsSize)
{
    int *const first = nums, *const last = nums + numsSize;
    if (!do_next_permutation(first, last)) reverse(first, last);
}
