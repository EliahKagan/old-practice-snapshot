#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> get_row(std::vector<int>::size_type n)
    {
        std::vector<int> row;
        for (row.reserve(n); n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            row.push_back(k);
        }

        return row;
    }
}

int main()
{
    std::vector<int>::size_type n {};
    std::cin >> n;

    auto sum = 0;
    for (std::vector<int>::size_type i {0u}; i != n; ++i) {
        const auto row = get_row(n);
        sum += row[i] - row[n - i - 1u];
    }

    std::cout << std::abs(sum) << '\n';
}
