#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    bool is_fascinating(const int n)
    {
        std::ostringstream ss;
        ss << n << n * 2 << n * 3;
        
        std::array<bool, 9> a {};
        for (const auto c : ss.str()) {
            if (c == '0') continue;
            const auto k = static_cast<decltype(a)::size_type>(c - '1');
            if (a[k]) return false;
            a[k] = true;
        }

        return std::all_of(a.cbegin(), a.cend(),
                           [](const bool b) { return b; });
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;
        
        // typo from specification, possibly required by solution checker
        if (n < 100) std::cout << "Number should be atleast three digits\n";
        else if (is_fascinating(n)) std::cout << "Fascinating\n";
        else std::cout << "Not Fascinating\n";
    }
}
