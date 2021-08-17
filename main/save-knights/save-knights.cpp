#include <iostream>

namespace {
    int max_knights(const int side_length)
    {
        const int area = side_length * side_length;
        return area - area / 2;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;
        std::cout << max_knights(n) << '\n';
    }
}
