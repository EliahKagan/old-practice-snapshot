#include <bitset>
#include <cstddef>
#include <iostream>
#include <memory>

int main()
{
    constexpr auto size = 1ul << 31;
    const auto ptr = std::make_unique<std::bitset<size>>();
    auto& bits = *ptr;

    std::size_t n {}, s {}, p {}, q {};
    std::cin >> n >> s >> p >> q;

    std::size_t i {0u};
    while (i != n && !bits[s]) {
        bits.set(s);
        s = (s * p + q) % size;
        ++i;
    }

    std::cout << i << '\n';
}
