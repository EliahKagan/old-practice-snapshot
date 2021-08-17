#ifdef _MSC_VER
#define NOMINMAX
#endif

#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <limits>
#include <vector>

namespace {
    std::vector<int> read_elements()
    {
        std::vector<int> a;
        decltype(a)::size_type n = 0u;
        std::cin >> n;
        assert(1u <= n && n <= 100u);
        a.reserve(n);

        for (auto i = n; i != 0u; --i) {
            auto k = 0;
            std::cin >> k;
            assert(1 <= k && k <= 100000);
            a.push_back(k);
        }

        return a;
    }

    int min_delta(const std::vector<int>& a)
    {
        auto min = std::numeric_limits<int>::max();

        for (auto i = a.size(); --i != 0u; ) {
            auto d = a[i] - a[i - 1];
            if (d < min) min = d;
        }

        return min;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = read_elements();
        std::sort(std::begin(a), std::end(a));
        std::cout << min_delta(a) << '\n';
    }
}
