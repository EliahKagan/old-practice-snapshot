#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> get(std::vector<int>::size_type n)
    {
        std::vector<int> a;
        a.reserve(n);

        for (; n != 0u; --n) {
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
        std::vector<int>::size_type n {}, d {};
        std::cin >> n >> d;
        assert(0u < n && d <= n);
        const auto a = get(n);

        auto sep = "";
        const auto print = [&sep](int k) {
            std::cout << sep << k;
            sep = " ";
        };

        const auto dd = static_cast<decltype(a)::difference_type>(d);
        assert(dd >= 0);
        auto q = a.cbegin() + dd;

        std::for_each(q, a.cend(), print);
        std::for_each(a.cbegin(), q, print);
        std::cout << '\n';
    }
}
