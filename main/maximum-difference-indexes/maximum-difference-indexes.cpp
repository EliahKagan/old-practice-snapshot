#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace {
    constexpr std::size_t xmax {1000u};

    using Indices = std::array<int, xmax + 1u>;

    void read_min_and_max_indices(Indices& min_indices, Indices& max_indices)
    {
        auto n = 0;
        std::cin >> n;

        for (auto i = 1; i <= n; ++i) { // 1-based "indexing"
            std::size_t x {};
            std::cin >> x;

            if (x > xmax) throw std::out_of_range{"element out of range"};

            if (min_indices[x] == 0) min_indices[x] = i;
            max_indices[x] = i;
        }
    }

    int read_maximum_index_difference()
    {
        Indices min_indices {}, max_indices {};
        read_min_and_max_indices(min_indices, max_indices);

        auto acc = 0;

        for (auto p = min_indices.cbegin(), q = max_indices.cbegin();
                    p != min_indices.cend(); ++p, ++q)
            acc = std::max(acc, *q - *p);

        return acc;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t)
        std::cout << read_maximum_index_difference() << '\n';
}
