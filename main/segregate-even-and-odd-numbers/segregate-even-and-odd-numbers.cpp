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
            auto k = 0;
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }

    void put(const std::vector<int>& a)
    {
        auto sep = "";
        for (const auto k : a) {
            std::cout << sep << k;
            sep = " ";
        }

        std::cout << '\n';
    }

    bool compare(const int lhs, const int rhs)
    {
        const auto lhs_parity = lhs % 2, rhs_parity = rhs % 2;
        return lhs_parity == rhs_parity ? lhs < rhs : lhs_parity < rhs_parity;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = get();
        std::sort(std::begin(a), std::end(a), compare);
        put(a);
    }
}
