#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> get()
    {
        std::vector<int> a;
        decltype(a)::size_type n = 0u;
        std::cin >> n;
        assert(n != 0u);
        a.reserve(n);

        do {
            auto k = 0;
            std::cin >> k;
            assert(k > 0);
            a.push_back(k);
        }
        while (--n != 0);

        return a;
    }

    void put_rearranged(std::vector<int>&& a)
    {
        assert(!a.empty()); // redundant assertion, in case get() is edited
        auto q = a.cend() - 1;
        std::cout << *q;

        auto p = a.cbegin();
        for (--q; p < q; ++p, --q) std::cout << ' ' << *p << ' ' << *q;
        if (p == q) std::cout << ' ' << *p;

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) put_rearranged(get());
}
