#include <cstddef>
#include <iostream>
#include <vector>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::size_t n {};
        std::cin >> n;
        std::vector<std::vector<int>> a (n, std::vector<int>(n));

        const auto size = n * n;
        for (std::size_t k {0u}; k != size; ++k) {
            auto elem = 0;
            std::cin >> elem;

            const auto i = k / n, j = k % n;
            a[j][n - i - 1] = elem;
        }

        for (const auto& row : a)
            for (const auto val : row) std::cout << val << ' ';

        std::cout << '\n';
    }
}
