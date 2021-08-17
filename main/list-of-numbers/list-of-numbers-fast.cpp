#ifdef _MSC_VER
#define NOMINMAX
#endif

#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

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

    // Checks if n > 0 has a representation length of k in any base.
    // Returns true if it does (i.e., if such a base is found).
    bool has_representation_length(const long long n, const long long k)
    {
        assert(n > 0LL);
        
        // Numbers representable with exactly k digits in base b are those
        // falling in the range [b**(k - 1), b**k). I use n**(1 / k) - 1 as a
        // lower bound approximation for b.
        const auto min_b = std::llround(std::pow(n, 1. / k)) - 1LL;
        for (auto b = std::max(min_b, 2LL); ; ++b) {
            const auto min_n = llpow(b, k - 1LL);
            if (n < min_n) return false; // too short in higher bases too
            if (n < min_n * b) return true;
        }
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0LL, k = 0LL;
        std::cin >> n >> k;
        std::cout << (has_representation_length(n, k) ? "YES" : "NO") << '\n';
    }
}
