enum { alpha_len = 26 };
_Static_assert('z' - 'a' + 1 == alpha_len, "noncontiguous lowercase letters");

char* customSortString(const char s[static restrict const 1],
                       char t[static restrict const 1])
{
    int ord[alpha_len] = {0};
    for (int i = 0; s[i]; ++i) ord[s[i] - 'a'] = i + 1;

    int compare(const void *const p, const void *const q) {
        const char lhs = *(const char *)p, rhs = *(const char *)q;
        return ord[lhs - 'a'] - ord[rhs - 'a'];
    }

    qsort(t, strlen(t), sizeof *t, compare);
    return t;
}
