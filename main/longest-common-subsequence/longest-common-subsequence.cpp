#ifdef _MSC_VER
#define NOMINMAX
#endif

#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {
    // Finds the length of the longest common subsequence of s and t, by an
    // iterative algorithm similar to the "Iterative LCS" method described in
    // https://www.ics.uci.edu/~eppstein/161/960229.html (Eppstein 1996).
    int lcslen(const std::string& s, const std::string& t)
    {
        const std::vector<int> blank_row (t.size() + 1u, 0);
        std::vector<std::vector<int>> a (s.size() + 1u, blank_row);

        for (auto i = s.size(); i-- != 0u; ) {
            for (auto j = t.size(); j-- != 0u; ) {
                a[i][j] = (s[i] == t[j]
                                ? 1 + a[i + 1u][j + 1u]
                                : std::max(a[i + 1u][j], a[i][j + 1u]));
            }
        }

        return a[0u][0u];
    }
}

int main()
{
    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        std::string::size_type slen {}, tlen {};
        std::cin >> slen >> tlen;
        
        std::string s, t;
        s.reserve(slen);
        t.reserve(tlen);
        std::cin >> s >> t;

        assert(s.size() == slen && t.size() == tlen);
        std::cout << lcslen(s, t) << '\n';
    }
}
