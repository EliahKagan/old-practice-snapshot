#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace {
    using Index = std::vector<int>::size_type;

    inline int compute_steps_to_zero(const Index n,
                                     const std::vector<int>& tab)
    {
        auto acc = tab[n - 1u];

        for (auto k = static_cast<Index>(std::sqrt(n)); k != 1u; --k)
            if (n % k == 0u) acc = std::min(acc, tab[n / k]);

        return acc + 1;
    }

    std::vector<int> build_steps_to_zero_table(const Index nmax)
    {
        const auto size = nmax + 1u;

        std::vector<int> tab;
        tab.reserve(size);

        tab.push_back(0);
        tab.push_back(1);

        for (Index n {2u}; n != size; ++n)
            tab.push_back(compute_steps_to_zero(n, tab));
        
        return tab;
    }
}

int main()
{
    constexpr Index nmax {1000000u};

    const auto tab = build_steps_to_zero_table(nmax);

    std::ios_base::sync_with_stdio(false);

    auto q = 0;
    for (std::cin >> q; q > 0; --q) {
        Index n {};
        std::cin >> n;
        std::cout << tab.at(n) << '\n';
    }
}
