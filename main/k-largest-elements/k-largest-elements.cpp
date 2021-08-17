#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <iostream>
#include <vector>

namespace {
    void print(const std::vector<int>& a)
    {
        auto sep = "";
        for (const auto x : a) {
            std::cout << sep << x;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int> a;
        decltype(a)::size_type n = 0u, k = 0u;
        std::cin >> n >> k;
        assert(k <= n);
        a.reserve(n);

        for (auto i = n; i != 0u; --i) {
            auto x = 0;
            std::cin >> x;
            a.push_back(x);
        }

        const auto comparer = std::greater<decltype(a)::value_type>();
        std::sort(std::begin(a), std::end(a), comparer);
        a.resize(k);

        print(a);
    }
}
