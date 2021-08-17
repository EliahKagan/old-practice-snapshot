enum { k_nowhere = -1 };

static int strLen(const char *const s)
{
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

int strStr(char* haystack, char* needle)
{
    const int jstop = strLen(needle), istop = strLen(haystack) - jstop + 1;
    if (istop < 0) return k_nowhere;

    for (int i = 0; i != istop; ++i) {
        int j = 0;
        while (j != jstop && haystack[i + j] == needle[j]) ++j;
        if (j == jstop) return i;
    }

    return k_nowhere;
}