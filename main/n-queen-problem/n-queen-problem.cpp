#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <array>
#include <cstdio>
#include <stdexcept>

namespace {
    constexpr std::size_t nmax {10u};

    using UsedRows = std::array<bool, nmax + 1u>;

    using Placements = std::array<std::size_t, nmax + 1u>;
    
    void print_solution(const std::size_t n, const Placements& queens)
    {
        std::putchar('[');

        const auto colstop = n + 1u;
        for (std::size_t col {1u}; col != colstop; ++col)
            std::printf("%zu ", queens[col]);

        std::fputs("] ", stdout);
    }

    inline bool has_diagonal_attack(const std::size_t n, const std::size_t col,
            const std::size_t row, const Placements& queens)
    {
        for (auto c = col, r = row; --c != 0u && --r != 0u; )
            if (queens[c] == r) return true;

        const auto rstop = n + 1u;
        for (auto c = col, r = row; --c != 0u && ++r != rstop; )
            if (queens[c] == r) return true;

        return false;
    }

    bool print_n_queens_solutions(const std::size_t n, UsedRows& used,
                                  const std::size_t col, Placements& queens)
    {
        auto found = false;

        const auto rowstop = n + 1u;
        for (std::size_t row {1u}; row != rowstop; ++row) {
            if (used[row] || has_diagonal_attack(n, col, row, queens))
                continue;

            queens[col] = row;

            if (col == n) {
                print_solution(n, queens);
                found = true;
            } else {
                used[row] = true;
                found |= print_n_queens_solutions(n, used, col + 1u, queens);
                used[row] = false;
            }
        }

        return found;
    }

    void print_all_n_queens_solutions(const std::size_t n)
    {
        if (n == 0u || n > nmax) throw std::out_of_range("n out of range");

        UsedRows used {};
        Placements queens {};

        if (print_n_queens_solutions(n, used, 1u, queens)) std::putchar('\n');
        else puts("-1");
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        std::size_t n {};
        (void)std::scanf("%zu", &n);
        print_all_n_queens_solutions(n);
    }
}
