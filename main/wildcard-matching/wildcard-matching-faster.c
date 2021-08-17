bool isMatch(char *restrict s, char *restrict p) {
    // match the front and advance past it
    for (; ; ++s, ++p) {
        switch (*p) {
        case '?':
            if (*s == '\0') return false;
            continue;
        case '*':
            break;
        case '\0':
            return *s == '\0';
        default:
            if (*s != *p) return false;
            continue;
        }
        break; // so break in the switch breaks the loop
    }

    // advance to what might be the first floating subpattern and check if done
    while (*p == '*') ++p;
    if (*p == '\0') return true;

    {
        // find the back
        char *restrict ss = s, *restrict pp = p;
        while (*ss != '\0') ++ss;
        while (*pp != '\0') ++pp;

        // match the back
        for (; ; ) {
            switch (*--pp) {
            case '?':
                if (ss == s) return false;
                --ss; // no need to check what character it points to
                continue;
            case '*':
                break;
            default:
                if (ss == s || *--ss != *pp) return false;
                continue;
            }
            break; // so break in the switch breaks the loop
        }

        // trim the back and check if done
        if (++pp == p) return true;
        *ss = *pp = '\0';
    }

    do {
        // greedily match a floating subpattern (TODO: use a fast KMP-like way)
        for (char *restrict ss = s, *restrict pp = p; ; ) {
            switch (*p) {
            case '?':
                if (*s == '\0') return false; // no later match is possible
                ++s;
                ++p;
                continue;
            case '*':
                break; // we got a match!
            default:
                if (*s == *p) {
                    ++s;
                    ++p;
                } else {
                    if (*s == '\0') return false; // no later match is possible
                    s = ++ss;
                    p = pp;
                }
                continue;
            }
            break; // so break in the switch breaks the loop
        }

        // advance to the next floating subpattern
        while (*++p == '*') { }
    }
    while (*p != '\0');

    return true;
}
