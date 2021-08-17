#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

namespace {
    constexpr std::size_t rmax {20u}, cmax {20u};
    using Rows = std::array<bool, rmax>;
    using Cols = std::array<bool, cmax>;

    void read_to_row_col_masks(Rows& rows, const std::size_t r,
                               Cols& cols, const std::size_t c)
    {
        assert (1u <= r && r <= rmax && 1u <= c && c <= cmax);

        for (std::size_t i {0u}; i != r; ++i) {
            for (std::size_t j {0u}; j != c; ++j) {
                bool b {};
                std::cin >> b;
                if (b) rows[i] = cols[j] = true;
            }
        }
    }

    void write_from_row_col_masks(const Rows& rows, const std::size_t r,
                                  const Cols& cols, const std::size_t c)
    {
        auto sep = "";

        for (std::size_t i {0u}; i != r; ++i) {
            for (std::size_t j {0u}; j != c; ++j) {
                std::cout << sep << (rows[i] || cols[j]);
                sep = " ";
            }
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::size_t r {}, c {};
        std::cin >> r >> c;

        Rows rows {};
        Cols cols {};

        read_to_row_col_masks(rows, r, cols, c);
        write_from_row_col_masks(rows, r, cols, c);
    }
}
