#include <bitset>
#include <climits>
#include <iostream>
#include <string>

namespace {
    bool is_sparse(unsigned long long n)
    {
        const auto s = std::bitset<CHAR_BIT * sizeof n>{n}.to_string();
        return s.find("11") == s.npos;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0uLL;
        std::cin >> n;
        std::cout << (is_sparse(n) ? '1' : '0') << '\n';
    }
}
