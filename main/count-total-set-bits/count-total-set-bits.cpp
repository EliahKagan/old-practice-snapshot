#include <bitset>
#include <climits>
#include <cstddef>
#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::size_t popcount {0u};
        
        auto n = 0uLL;
        for (std::cin >> n; n != 0uLL; --n)
            popcount += std::bitset<CHAR_BIT * sizeof n>{n}.count();

        std::cout << popcount << '\n';
    }
}
