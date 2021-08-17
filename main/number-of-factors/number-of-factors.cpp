#include <cmath>
#include <iostream>

namespace {
    int count_divisors(const long n)
    {
        auto count = 0L;
        auto stop = std::lround(std::ceil(std::sqrt(static_cast<double>(n))));

        for (auto i = 1L; i < stop; ++i)
            if (n % i == 0L) ++count;

        return stop * stop == n ? count * 2L + 1L : count * 2L;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0L;
        std::cin >> n;
        std::cout << count_divisors(n) << '\n';
    }
}
