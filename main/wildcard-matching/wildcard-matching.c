bool isMatch(char *s, char *p) {
    for (; ; ++s, ++p) {
        switch (*p) {
        case '\0':
            return *s == '\0';

        case '*':
            while (*++p == '*') { } // consolidate successive * wildcards
            char *t = s;

            do
                if (isMatch(t, p)) return true;
            while (*t++ != '\0');

            return false;

        case '?':
            if (*s == '\0') return false;
            continue;

        default:
            if (*s != *p) return false;
            continue;
        }
    }
}
