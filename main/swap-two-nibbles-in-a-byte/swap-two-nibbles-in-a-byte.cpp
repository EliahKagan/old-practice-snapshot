#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>

int main()
{
    constexpr auto mask  = 0xFFu;        // a byte is 8 bits, in this context
    constexpr auto width = 4u; //-V112   // a nibble is 4 bits

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto x = 0u;
        std::cin >> x;
        assert(x != 0u && (x & mask) == x);
        std::cout << ((x >> width | x << width) & mask) << '\n';
    }
}
