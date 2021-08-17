#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <algorithm>
#include <bitset>
#include <climits>
#include <iostream>
#include <string>

namespace {
    std::string BinaryAdd(const std::string& x, const std::string& y)
    {
        using Bits = std::bitset<sizeof(unsigned long long) * CHAR_BIT>;

        const Bits sum_bits {Bits{x}.to_ullong() + Bits{y}.to_ullong()};
        const auto sum_wide = sum_bits.to_string();

        const auto msb_pos = std::min(sum_wide.find('1'), sum_wide.size());
        const auto sum = sum_wide.substr(msb_pos);

        const auto size = std::max(x.size(), y.size());
        return size > sum.size() ? std::string(size - sum.size(), '0') + sum
                                 : sum;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string x, y;
        std::cin >> x >> y;
        std::cout << BinaryAdd(x, y) << '\n';
    }
}
