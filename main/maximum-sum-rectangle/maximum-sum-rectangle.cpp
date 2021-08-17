#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <algorithm>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
    using Matrix = std::vector<std::vector<int>>;
    
    Matrix read_row_running_sums(const std::size_t r, const std::size_t c)
    {
        Matrix row_sums (r);
        
        for (auto& row : row_sums) {
            row.reserve(c + 1u);
            
            auto acc = 0;
            row.push_back(acc);
            
            for (auto j = c; j != 0u; --j) {
                auto x = 0;
                (void)std::scanf("%d", &x);
                row.push_back(acc += x);
            }
        }
        
        return row_sums;
    }
    
    std::vector<int> calc_rect_running_sum(const Matrix& row_sums,
            const std::size_t left, const std::size_t right)
    {
        std::vector<int> rect;
        rect.reserve(row_sums.size() + 1u);
        
        auto acc = 0;
        rect.push_back(acc);
        
        for (const auto& row : row_sums)
            rect.push_back(acc += row[right] - row[left]);
        
        return rect;
    }
    
    int read_matrix_max_rectangle_sum(const std::size_t r, const std::size_t c)
    {
        if (r == 0u || c == 0u)
            throw std::out_of_range{"0-element matrices are not supported"};
        
        const auto row_sums = read_row_running_sums(r, c);
        auto best = std::numeric_limits<int>::min();
        
        for (std::size_t left {0u}; left != c; ++left) {
            for (auto right = left + 1u; right <= c; ++right) {
                const auto rect = calc_rect_running_sum(row_sums, left, right);
                
                for (std::size_t top {0u}; top != r; ++top) {
                    for (auto bot = top + 1u; bot <= r; ++bot)
                        best = std::max(best, rect[bot] - rect[top]);
                }
            }
        }
        
        return best;
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        std::size_t r {}, c {};
        (void)std::scanf("%zu%zu", &r, &c);
        
        std::printf("%d\n", read_matrix_max_rectangle_sum(r, c));
    }
}
