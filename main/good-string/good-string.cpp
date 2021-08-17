#include <cstdlib>
#include <iostream>
#include <string>

namespace {
    bool is_good(const std::string s)
    {
        const auto n = s.size();
        if (n < 2) return true;
        
        for (std::string::size_type i {0u}, j {1u}; j != n; ++i, ++j) {
            switch (std::abs(s[i] - s[j])) {
                case 1: case 25:    continue;
                default:            return false;
            }
        }
        
        return true;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::cout << (is_good(s) ? "YES" : "NO") << '\n';
    }
}
