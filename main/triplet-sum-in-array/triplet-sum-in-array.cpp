#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    // Returns a vector of n ints read from standard input.
    std::vector<int> get(std::vector<int>::size_type n)
    {
        std::vector<int> a;
        for (a.reserve(n); n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }

    // Determines if any two values accessed by iterators in [p, q) sum to x.
    // Elements in the specified range are assumed to be sorted.
    inline bool has_twin_sum(std::vector<int>::const_iterator p,
            const std::vector<int>::const_iterator& q, const int x)
    {
        while (p != q) {
            const auto key = x - *p;
            if (*p > key) return false;
            if (std::binary_search(++p, q, key)) return true;
        }

        return false;
    }

    // Determines if any three values in a sorted vector a sum to the value x.
    bool has_triplet_sum(const std::vector<int>& a, const int x)
    {
        const auto max_possible = x / 3;

        for (auto p = a.cbegin(); p != a.cend() && *p <= max_possible; ) {
            const auto remaining_sum = x - *p;
            if (has_twin_sum(++p, a.cend(), remaining_sum)) return true;
        }

        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        auto x = 0;
        std::cin >> n >> x;

        auto a = get(n);
        std::sort(a.begin(), a.end());

        std::cout << has_triplet_sum(a, x) << '\n';
    }
}
