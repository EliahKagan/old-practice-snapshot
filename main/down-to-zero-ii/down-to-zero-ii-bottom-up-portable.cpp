#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

namespace {
    using Index = std::vector<int>::size_type;

    std::vector<int> build_steps_to_zero_table(const Index nmax)
    {
        const auto size = nmax + 1u;
        const auto root = static_cast<Index>(std::sqrt(nmax));

        std::vector<int> tab (size, std::numeric_limits<int>::max());
        tab[0u] = 0;
        tab[1u] = 1;

        for (Index big_factor {2u}; big_factor != size; ++big_factor) {
            tab[big_factor] = std::min(tab[big_factor],
                                       tab[big_factor - 1u] + 1);

            const auto max_product =
                    (big_factor > root ? nmax : big_factor * big_factor);

            for (auto product = big_factor; product <= max_product;
                                             product += big_factor)
                tab[product] = std::min(tab[product], tab[big_factor] + 1);
        }

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