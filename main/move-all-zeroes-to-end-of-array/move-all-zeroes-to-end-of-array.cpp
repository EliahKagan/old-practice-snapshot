#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto z = 0, n = 0;
        for (std::cin >> n; n > 0; --n) {
            auto k = 0;
            std::cin >> k;
            if (k == 0) ++z;
            else std::cout << k << ' ';
        }

        while (z-- > 0) std::cout << 0 << ' ';
        std::cout << '\n';
    }
}
