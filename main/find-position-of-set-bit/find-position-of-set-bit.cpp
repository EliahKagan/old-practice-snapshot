#include <iostream>

namespace {
    int lsb_pos(const int n)
    {
        constexpr auto width = 30;

        for (auto i = 0; i != width; ++i) {
            const auto bit = 1 << i;
            if (n & bit) return n == bit ? i + 1 : -1;
        }

        return -1;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;
        std::cout << lsb_pos(n) << '\n';
    }
}
