#include <iostream>
#include <vector>

namespace {
    std::vector<int> get()
    {
        std::vector<int> a;
        typename decltype(a)::size_type n {0u};
        std::cin >> n;
        a.reserve(n);

        for (; n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }

    // Counts the number of "matching" subsequences. A subsequence "matches" if
    // its length is at least 2 and it is strictly increasing.
    std::vector<int>::difference_type subseq_match_count(std::vector<int>&& a)
    {
        std::vector<int>::difference_type count {0};

        for (auto p = a.cbegin(), q = p; p != a.cend(); p = q) {
            while (++q != a.cend() && *(q - 1) < *q) { }
            const auto d = q - p;
            if (d > 1) count += d * (d - 1) / 2;
        }

        return count;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t)
        std::cout << subseq_match_count(get()) << '\n';
}
