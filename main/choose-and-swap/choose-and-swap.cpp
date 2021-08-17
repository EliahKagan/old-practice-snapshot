#include <iostream>
#include <string>
#include <unordered_set>

namespace {
    bool get_swappable_chars(const std::string& s, char& high, char& low)
    {
        constexpr auto none = '\0';
        high = low = none;

        if (s.size() < 2u) return true;
        const auto istop = s.size() - 1u;
        std::unordered_set<char> noswap;

        for (std::string::size_type i {0u}; i != istop; ++i) {
            if (noswap.find(s[i]) != noswap.end()) continue;

            for (auto j = i; ++j != s.size(); ) {
                if (s[i] > s[j] && noswap.find(s[j]) == noswap.end()
                                && (s[j] < low || low == none))
                    low = s[j];
            }

            if (low != none) {
                high = s[i];
                return true;
            }

            noswap.insert(s[i]);
        }

        return false;
    }

    void swap_chars(std::string& s, const char first, const char second)
    {
        for (char& c : s) {
            if (c == first) c = second;
            else if (c == second) c = first;
        }
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;

        char high, low;
        if (get_swappable_chars(s, high, low)) swap_chars(s, high, low);
        std::cout << s << '\n';
    }
}
