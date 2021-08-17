#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

namespace {
    template<typename T>
    std::vector<T> get(const typename std::vector<T>::size_type n)
    {
        std::vector<T> a;
        a.reserve(n);

        for (auto i = n; i != 0u; --i) {
            T x {};
            std::cin >> x;
            a.push_back(x);
        }

        assert(a.size() == n);
        return a;
    }

    template<typename T>
    void put(const std::vector<T>& a)
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
        std::vector<int>::size_type n = 0u, k = 0u;
        std::cin >> n >> k;
        assert(1u <= k && k <= n && n <= 500u);
        auto a = get<int>(n);
        std::swap(a[k - 1], a[n - k]);
        put(a);
    }
}
