#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int>::difference_type
    max_contiguous_length(const std::vector<int>& seq)
    {
        if (seq.empty()) return 0u;

        std::vector<int>::difference_type len {0};
        
        auto p = seq.cbegin();
        auto prev = *p;
        auto q = p;

        while (++q != seq.cend()) {
            if (++prev == *q) continue;

            prev = *q;
            len = std::max(len, q - p);
            p = q;
        }

        return std::max(len, q - p);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        std::cin >> n;
        std::vector<int> seq;
        
        for (seq.reserve(n); n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            seq.push_back(k);
        }

        std::sort(seq.begin(), seq.end());
        seq.erase(std::unique(seq.begin(), seq.end()), seq.end());
        std::cout << max_contiguous_length(seq) << '\n';
    }
}
