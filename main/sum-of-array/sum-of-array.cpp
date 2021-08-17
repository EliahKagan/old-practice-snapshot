#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto sum = 0, n = 0;
        
        for (std::cin >> n; n > 0; --n) {
            auto k = 0;
            std::cin >> k;
            sum += k;
        }

        std::cout << sum << '\n';
    }
}
