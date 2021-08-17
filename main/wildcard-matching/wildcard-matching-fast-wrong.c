static bool isMatchGreedy(const char *s, const char *const ss,
                          const char *restrict p)
{
    for (; ; ++s, ++p) {
        switch (*p) {
        case '\0':
            return s == ss;

        case '*':
            while (*++p == '*') { }  // consolidate successive * wildcards

            for (const char *t = ss; t != s; --t) // match 1+ chars to *
                if (isMatchGreedy(t, ss, p)) return true;

            continue;  // match 0 chars to *

        case '?':
            if (s == ss) return false;
            continue;

        default:
            if (*s != *p) return false;
            continue;
        }
    }
}

bool isMatch(char *s, char *p) {
    return isMatchGreedy(s, strchr(s, '\0'), p);
}
