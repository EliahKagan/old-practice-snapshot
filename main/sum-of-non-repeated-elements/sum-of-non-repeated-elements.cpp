#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

namespace {
    template<typename T>
    std::vector<T> get()
    {
        std::vector<T> a;
        typename decltype(a)::size_type n {0u};
        std::cin >> n;
        a.reserve(n);

        for (; n != 0u; --n) {
            T x {};
            std::cin >> x;
            a.push_back(x);
        }

        return a;
    }

    template<typename T>
    T sum_unique(std::vector<T>&& a, const T zero)
    {
        std::sort(a.begin(), a.end());
        const auto end = std::unique(a.begin(), a.end());
        a.erase(end, a.end());
        return std::accumulate(a.cbegin(), a.cend(), zero);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t)
        std::cout << sum_unique(get<int>(), 0) << '\n';
}
