#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {
    std::vector<std::pair<char, char>> read_ends()
    {
        std::vector<std::pair<char, char>>::size_type n {};
        std::cin >> n;

        std::vector<std::pair<char, char>> pairs;
        pairs.reserve(n);

        while (n-- != 0u) {
            std::string s;
            std::cin >> s;

            assert(!s.empty());
            pairs.emplace_back(s.front(), s.back());
        }

        return pairs;
    }

    
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {

    }
}
