#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

namespace {
    std::vector<int> get()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;

        std::vector<int> a;
        for (a.reserve(n); n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto a = get();
        assert(!a.empty());
        
        decltype(a)::const_iterator p, q;
        std::tie(p, q) = std::minmax_element(a.cbegin(), a.cend());
        std::cout << *q << ' ' << *p << '\n';
    }
}
