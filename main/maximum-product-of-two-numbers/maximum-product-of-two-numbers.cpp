#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto high = 0, low = 0, n = 0;

        for (std::cin >> n; n > 0; --n) {
            auto k = 0;
            std::cin >> k;

            if (k >= high) {
                low = high;
                high = k;
            }
            else if (k > low) low = k;
        }

        std::cout << high * low << '\n';
    }
}
