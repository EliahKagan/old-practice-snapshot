static bool isMatchGreedy(const char *s, const char *const ss,
                          const char *restrict p)
{
    for (; ; ) {
        switch (*p) {
        case '*':
            while (*++p == '*') { }  // consolidate successive * wildcards

            for (const char *t = ss; t != s; --t) // try to match 1+ chars to *
                if (isMatchGreedy(t, ss, p)) return true;

            continue; // match 0 chars to * (don't increment s or p this time)

        case '?':
            if (s == ss) return false;
            break;

        case '\0':
            return s == ss;

        default:
            if (*s != *p) return false;
            break;
        }

        ++s;
        ++p;
    }
}

bool isMatch(char *s, char *p) {
    return isMatchGreedy(s, strchr(s, '\0'), p);
}
