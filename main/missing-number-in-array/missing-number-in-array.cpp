#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<std::size_t> a;
        decltype(a)::size_type i = 0u;
        std::cin >> i;
        assert(i != 0u); // due to problem constraints, this should hold
        a.reserve(i);

        a.push_back(0);
        while (--i != 0u) {
            std::size_t k = 0u;
            std::cin >> k;
            assert(std::cin); // value successfully read
            a.push_back(k);
        }

        std::sort(std::begin(a), std::end(a));
        while (++i != a.size() && a[i] == i) { }
        std::cout << i << '\n';
    }
}
