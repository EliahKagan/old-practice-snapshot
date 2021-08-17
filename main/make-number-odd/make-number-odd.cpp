#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, d = 1;
        for (std::cin >> n; n % 2 == 0; n /= 2) d *= 2;
        std::cout << d << '\n';
    }
}
