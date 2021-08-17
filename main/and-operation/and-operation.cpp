#include <cstdint>
#include <iostream>

namespace {
    std::uint32_t conj_range(const std::uint32_t a, const uint32_t b)
    {
        auto n = a ^ b;
        for (std::uint32_t i {1u}; i <= 16u; i *= 2u) n |= n >> i;
        return a & ~n;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        // Problem constraints allow 2^32 for b. This behaves the same
        // as 0 in in conj_range(), but extracting into a uint32_t doesn't
        // wrap around, so I extract to a variable of larger type first.
        std::uint32_t a {};
        std::uint_fast64_t b {};
        std::cin >> a >> b;
        std::cout << conj_range(a, static_cast<std::uint32_t>(b)) << '\n';
    }
}
