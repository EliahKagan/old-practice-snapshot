#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    // Computes integer powers.
    long long llpow(const long long base, const long long exponent)
    {
        if (exponent < 2LL) return exponent == 1LL ? base : 1LL;

        const auto divmod2 = std::lldiv(exponent, 2LL);
        const auto root = llpow(base, divmod2.quot);
        const auto square = root * root;
        return divmod2.rem == 0LL ? square : square * base;
    }

    // Computes the kth least significant digit (i.e., from the right) of a**b.
    char kth_lsd(const long long a, const long long b,
                 const std::string::size_type k)
    {
        std::ostringstream ss;
        ss << llpow(a, b);
        const auto s = ss.str();
        return s.at(s.size() - k);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        long long a {}, b {};
        std::string::size_type k {};
        std::cin >> a >> b >> k;
        std::cout << kth_lsd(a, b, k) << '\n';
    }
}
