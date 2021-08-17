#include <algorithm>
#include <iostream>
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

    std::vector<int>::difference_type count_smaller(
            std::vector<int>::const_iterator p,         // *p must be valid
            const std::vector<int>::const_iterator& q)  // q is end iterator
    {
        const auto k = *p;
        return std::count_if(++p, q, [k](const int i) { return i < k; });
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto a = get();
        const auto q = a.cend();

        auto sep = "";
        for (auto p = a.cbegin(); p != q; ++p) {
            std::cout << sep << count_smaller(p, q);
            sep = " ";
        }

        std::cout << '\n';
    }
}
