#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = 0, b = 0, n = 0;
        std::cin >> a >> b >> n;
        std::cout << a + (b - a) * (n - 1) << '\n';
    }
}
