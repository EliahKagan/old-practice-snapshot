#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    std::vector<int> get()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;

        std::vector<int> a;
        for (a.reserve(n); n != 0u; --n) {
            int x {};
            std::cin >> x;
            a.push_back(x);
        }

        return a;
    }

    void put(const std::vector<int>& a)
    {
        const auto q = a.cend();
        auto p = a.cbegin();
        
        if (p != q) {
            std::cout << *p;
            while (++p != q) std::cout << ' ' << *p;
        }

        std::cout << '\n';
    }

    std::vector<int> compute_subset_sums(const std::vector<int>& a)
    {
        const auto len = a.size();
        const auto n = static_cast<decltype(len)>(1u) << len;
        std::vector<int> sums;
        sums.reserve(n);

        for (std::vector<int>::size_type i {0u}; i != n; ++i) {
            auto bits = i;
            auto sum = 0;

            for (std::vector<int>::size_type j {0u}; j != len; ++j) {
                if ((bits & 1u) != 0u)
                    sum += a[j]; //-V127 a[j] <= 100, len <= 10, max sum = 1000

                bits >>= 1u;
            }

            sums.push_back(sum);
        }

        std::sort(std::begin(sums), std::end(sums));
        return sums;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) put(compute_subset_sums(get()));
}
