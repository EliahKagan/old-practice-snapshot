#include <algorithm>
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

    // Checks if two values, in two distinct positions in a (though they may be
    // equal) sum to x. Returns true if such values exist, false otherwise.
    bool has_pair_sum(std::vector<int>&& a, const int x)
    {
        using std::binary_search;

        std::sort(a.begin(), a.end());

        // initialize iterator and handle empty case
        auto p = a.cbegin();
        if (p == a.cend()) return false;

        // handle leftmost item specially
        const auto front_dual = x - *p;
        if (front_dual >= *p && binary_search(p + 1, a.cend(), front_dual))
            return true;

        // handle remaining list items (starting with the second)
        while (++p != a.cend()) {
            const auto dual = x - *p;
            if (dual < *p ? binary_search(a.cbegin(), p, dual)
                          : binary_search(p + 1, a.cend(), dual))
                return true;
        }

        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n = 0u;
        auto x = 0;
        std::cin >> n >> x;
        std::cout << (has_pair_sum(get(n), x) ? "Yes" : "No") << '\n';
    }
}
