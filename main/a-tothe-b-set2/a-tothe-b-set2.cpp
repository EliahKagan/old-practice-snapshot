#include <iostream>

namespace {
    long long modular_pow(const long long n, const int p)
    {
        constexpr auto m = 1000000007LL;

        if (p < 2) return p == 0 ? 1LL : n;
        const auto r = modular_pow(n, p / 2), s = r * r % m;
        return p % 2 == 0 ? s : s * n % m;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        long long n {};
        int p {};
        std::cin >> n >> p;
        std::cout << modular_pow(n, p) << '\n';
    }
}
