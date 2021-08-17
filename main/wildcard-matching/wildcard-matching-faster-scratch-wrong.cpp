#include <iostream>
#include <iterator>
#include <string>

static bool isMatch(std::string::iterator s, std::string::iterator p) {
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
        std::string::iterator ss = s, pp = p;
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
        for (std::string::iterator ss = s, pp = p; ; s = ++ss, p = pp) {
            while (*s == *p && *p != '*') ++s, ++p;
            if (*p == '*') break;           // we got a match!
            if (*s == '\0') return false;   // no later match is possible
        }

        // advance to the next floating subpattern
        while (*++p == '*') {}
    } while (*p != '\0');

    return true;
}

int main() {
    std::string s {"crabapplefloridianbirthsnappersbob"};
    std::string p {"cra*bap**ple*ori*bi?t?s??p*ob"};
    s.push_back('\0');
    p.push_back('\0');

    std::cout << std::boolalpha
              << isMatch(std::begin(s), std::begin(p)) << '\n';
}
