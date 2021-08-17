// Generates well-formed input for testing boolean-parenthesization.cpp.

#include <array>
#include <cstddef>
#include <iostream>
#include <random>
#include <stdexcept>

namespace {
    using RandomRange = std::uniform_int_distribution<std::size_t>;

    constexpr std::array<char, 2u> terms {{'T', 'F'}};
    constexpr std::array<char, 3u> opers {{'&', '|', '^'}};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    std::default_random_engine eng{std::random_device{}()};
    RandomRange term_dist{0u, terms.size() - 1u};
    RandomRange oper_dist{0u, opers.size() - 1u};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    void emit_formula(int expr_len)
    {
        if (expr_len < 0)
            throw std::out_of_range{"formula must have nonnegative length"};

        if (expr_len % 2 == 0)
            throw std::invalid_argument{"formula must have odd length"};

        std::cout << expr_len << '\n';

        do {
            std::cout << (expr_len % 2 == 0 ? opers[oper_dist(eng)]
                                            : terms[term_dist(eng)]);
        }
        while (--expr_len != 0);

        std::cout << '\n';
    }
}

int main()
{
    constexpr auto maxlen = 99; // emit formulas up to this length
    auto count = 500;           // the number of formulas to emit

    std::ios_base::sync_with_stdio(false);
    std::cout << count << '\n';
    
    for (auto len = 1; len < maxlen && count > 0; len += 2)
        for (auto i = 3; i != 0 && count > 0; --i, --count) emit_formula(len);

    for (; count > 0; --count) emit_formula(maxlen);
}
