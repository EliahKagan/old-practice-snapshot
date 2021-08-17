#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>

namespace {
    // Computes greatest common divisor (a.k.a. highest common factor / HCF)
    // recursively by Euclid's algorithm.
    int gcd(const int m, const int n)
    {
        return n == 0 ? m : gcd(n, m % n);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = 0, b = 0;
        std::cin >> a >> b;
        assert(1 <= a && a <= 1000 && 1 <= b && b <= 1000);

        const auto hcf = gcd(a, b);
        std::cout << a * b / hcf << ' ' << hcf << '\n';
    }
}
