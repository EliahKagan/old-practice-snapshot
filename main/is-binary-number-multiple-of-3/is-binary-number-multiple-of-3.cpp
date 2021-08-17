#include <array>
#include <cstddef>
#include <iostream>
#include <string>

namespace {
    // Tells if the number represented by binary digits in n is multiple of 3.
    bool check_multiple(const std::string& n)
    {
        std::array<int, 2> counts {}; // counts set bits in even/odd positions

        for (std::size_t i {0u}; i != n.size(); ++i)
            if (n[i] == '1') ++counts[i % counts.size()];

        return (counts[0u] - counts[1u]) % 3 == 0;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) {
        std::string n;
        std::getline(std::cin, n);
        std::cout << check_multiple(n) << '\n';
    }
}
