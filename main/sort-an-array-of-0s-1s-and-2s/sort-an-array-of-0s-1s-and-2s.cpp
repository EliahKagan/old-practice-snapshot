#include <array>
#include <cstddef>
#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::array<int, 3> counts {};
        
        auto n = 0;
        for (std::cin >> n; n > 0; --n) {
            std::size_t i {};
            std::cin >> i;
            ++counts.at(i);
        }

        auto sep = "";
        for (std::size_t i {0u}; i != counts.size(); ++i) { // 0, 1, 2
            for (; counts[i] != 0; --counts[i]) {
                std::cout << sep << i;
                sep = " ";
            }
        }

        std::cout << '\n';
    }
}
