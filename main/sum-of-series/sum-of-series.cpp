#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;
        std::cout << n * (n + 1) / 2 << '\n';
    }
}
