enum { alpha_len = 26 };
_Static_assert('z' - 'a' + 1 == alpha_len, "noncontiguous lowercase letters");

static int compare(const void *const p, const void *const q, void *const aux)
{
    const int *const ord = aux;
    const char lhs = *(const char *)p, rhs = *(const char *)q;
    return ord[lhs - 'a'] - ord[rhs - 'a'];
}

char* customSortString(const char s[static restrict const 1],
                       char t[static restrict const 1])
{
    void qsort_r(void *, size_t, size_t,
                 int (*)(const void *, const void *, void *), void*);

    int ord[alpha_len] = {0};
    for (int i = 0; s[i]; ++i) ord[s[i] - 'a'] = i + 1;

    qsort_r(t, strlen(t), sizeof *t, compare, ord);
    return t;
}
