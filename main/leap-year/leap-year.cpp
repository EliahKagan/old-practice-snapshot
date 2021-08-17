#include <iostream>

namespace {
    bool is_leap_year(int n)
    {
        return n % 4 == 0 && (n % 400 == 0 || n % 100 != 0);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;
        std::cout << (is_leap_year(n) ? "Yes" : "No") << '\n';
    }
}
