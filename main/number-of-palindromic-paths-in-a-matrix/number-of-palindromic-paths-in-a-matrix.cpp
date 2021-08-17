#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>

namespace {
    using std::size_t;
    
    constexpr size_t rcmax {10u};
    
    using Grid = std::array<std::array<char, rcmax>, rcmax>;
    
    Grid read_grid(const size_t r, const size_t c)
    {
        if (r > rcmax || c > rcmax) throw std::out_of_range{"grid too big"};
        
        Grid a {};
        
        for (size_t i {0u}; i != r; ++i)
            for (size_t j {0u}; j != c; ++j) std::cin >> a[i][j];
        
        return a;
    }
    
    // For the biggest grid, binom((10 - 1) + (10 - 1), (10 - 1)) = 48,620
    // distinct paths. There should be enough time to check them all.
    int count_palindrome_paths(const Grid& a, const size_t r, const size_t c)
    {
        const auto steps = r + c - 2u;
        if (steps == 0u) return 1; // singleton case
        const auto midpoint = (steps + 1u) / 2u;
        const auto has_middle = steps % 2u == 0u;

        std::stack<char> history;
        
        const std::function<int(size_t, size_t)>
        second_half {[&, r, c, steps](const size_t i, const size_t j) {
            if (i == r || j == c || history.top() != a[i][j]) return 0;
            
            if (i + j == steps) return 1;
            
            history.pop();
            const auto ret = second_half(i, j + 1u) + second_half(i + 1u, j);
            history.push(a[i][j]);
            
            return ret;
            
        }};
        
        const auto bridge = [&, has_middle](const size_t i, const size_t j) {
            return has_middle ? second_half(i, j + 1u) + second_half(i + 1u, j)
                              : second_half(i, j);
        };
        
        const std::function<int(size_t, size_t)>
        first_half {[&, r, c, midpoint](const size_t i, const size_t j) {
            if (i == r || j == c) return 0;
            
            if (i + j == midpoint) return bridge(i, j);
            
            history.push(a[i][j]);
            const auto ret = first_half(i, j + 1u) + first_half(i + 1u, j);
            history.pop();
            
            return ret;
        }};
        
        return first_half(0u, 0u);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        size_t r {}, c {};
        std::cin >> r >> c;
        
        const auto a = read_grid(r, c);
        std::cout << count_palindrome_paths(a, r, c) << '\n';
    }
}
