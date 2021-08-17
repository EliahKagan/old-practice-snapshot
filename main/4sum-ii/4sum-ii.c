static int cmp(const void *const lhsp, const void *const rhsp)
{
    // Quickly compares ints of small magnitude. DO NOT use this to compare
    // ints whose difference might be less than INT_MIN or more than INT_MAX!
    return *(const int *)lhsp - *(const int *)rhsp;
}

static int twoSumCount(const int *restrict const xs, const int xslen,
                       const int *restrict const ys, const int yslen,
                       const int target)
{
    int count = 0;

    const int istop = xslen, jstop = -1;
    for (int i = 0, j = yslen - 1; i != istop && j != jstop; ) {
        const int x = xs[i], y = ys[j], sum = x + y;

        if (sum == target) {
            int di = 1, dj = 1;
            while (++i != istop && xs[i] == x) ++di;
            while (--j != jstop && ys[j] == y) ++dj;
            count += di * dj;
        }
        else if (sum < target) ++i;
        else --j;
    }

    return count;
}

int fourSumCount(int *restrict const a, const int alen,
                 int *restrict const b, const int blen,
                 int *restrict const c, const int clen,
                 int *restrict const d, const int dlen)
{
    qsort(c, (size_t)clen, sizeof *c, cmp);
    qsort(d, (size_t)dlen, sizeof *d, cmp);

    int count = 0;
    for (int h = 0; h != alen; ++h) {
        for (int k = 0; k != blen; ++k)
            count += twoSumCount(c, clen, d, dlen, -a[h] - b[k]);
    }

    return count;
}
