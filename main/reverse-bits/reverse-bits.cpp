#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    unsigned long long reverse32bits(const unsigned long long x)
    {
        const auto s = std::bitset<32>{x}.to_string();
        std::ostringstream ss;
        std::for_each(s.crbegin(), s.crend(), [&](const char d) { ss << d; });
        return std::bitset<32>{ss.str()}.to_ullong();
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        unsigned long long x {};
        std::cin >> x;
        std::cout << reverse32bits(x) << '\n';
    }
}
