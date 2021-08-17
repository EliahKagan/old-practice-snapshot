#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    using Size = typename std::vector<int>::size_type;
    using Count = typename std::vector<int>::difference_type;

    // Returns a vector of n ints read from standard input.
    std::vector<int> get(Size n)
    {
        std::vector<int> a;
        for (a.reserve(n); n != 0u; --n) {
            auto elem = 0;
            std::cin >> elem;
            a.push_back(elem);
        }

        return a;
    }

    // Counts pairs of integers in a that add to produce k. (Mutates a.)
    Count count_pairs(std::vector<int>&& a, const int k)
    {
        std::sort(a.begin(), a.end());
        Count count {0};

        for (auto p = a.cbegin(); p != a.cend(); ) {
            const auto elem = *p, key = k - elem;
            ++p;
            
            if (key < elem) continue; // a simple optimization

            const auto range = std::equal_range(p, a.cend(), key);
            count += range.second - range.first;
        }

        return count;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Size n {};
        auto k = 0;
        std::cin >> n >> k;
        std::cout << count_pairs(get(n), k) << '\n';
    }
}
