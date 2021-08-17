#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <bitset>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>

int main()
{
    static_assert(sizeof(int) >= 4, "int must be at least 32 bits");
    static_assert(sizeof(std::size_t) == 8, "64-bit host expected");
    constexpr std::size_t size {2147483648u}; // 2 ** 31    //-V101 //-V112

    int n;
    std::size_t s, p, q;
    std::cin >> n >> s >> p >> q;
    assert(std::cin && n > 0 && s < size && p < size && q < size);

    std::unique_ptr<std::bitset<size>> bits {new std::bitset<size>{}};
    bits->set(s);

    while (--n != 0u) {
        s = (s * p + q) % size;
        bits->set(s);
    }

    std::cout << bits->count() << '\n';
}
