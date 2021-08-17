#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>

namespace {
    using Limits = std::numeric_limits<char>;

    constexpr auto array_size
            = static_cast<std::size_t>(Limits::max() - Limits::min() + 1);
}

int main()
{
    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) {
        std::string s;
        std::getline(std::cin, s);
        
        std::array<bool, array_size> a {};
        for (const auto c : s) {
            const auto i = static_cast<std::size_t>(c - Limits::min());
            if (a[i]) continue;
            std::cout << c;
            a[i] = true;
        }

        std::cout << '\n';
    }
}
