#include <cstddef>
#include <iostream>

namespace {
    constexpr auto alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    constexpr bool have_contiguous_alphabet(const char *const p = alphabet, std::ptrdiff_t i = 0)
    {
        //std::cout << *p << ' ' << *p - 'A' << ' ' << i << '\n';

        return *p == '\0' || (static_cast<std::ptrdiff_t>(*p - 'A') == i
                              && have_contiguous_alphabet(p + 1, i + 1));
    }

    static_assert(have_contiguous_alphabet(), "needs contiguous upper-case letters");

    /*
    constexpr bool have_contiguous_alphabet()
    {
        for (const auto c : "ABCDEFGHIJKLMNOPQRSTUVWXUZ") { }
        return true;
    }
    */
}

int main()
{
    std::cout << std::boolalpha << have_contiguous_alphabet() << '\n';
}
