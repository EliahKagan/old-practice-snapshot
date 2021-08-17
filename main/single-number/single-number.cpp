#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto ans = 0;

        auto n = 0;
        for (std::cin >> n; n > 0; --n) {
            auto k = 0;
            std::cin >> k;
            ans ^= k;
        }

        std::cout << ans << '\n';
    }
}
