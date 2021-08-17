#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

namespace {
    constexpr bool is_digit(const char d) { return '0' <= d && d <= '9'; }

    std::string discern_type(const std::string& str)
    {
        if (str.empty()) return "string";

        const auto p = str.cbegin(), q = str.cend();
        const auto s = static_cast<std::string::difference_type>(str.size());
        const auto n = std::count_if(p, q, is_digit);

        if (n == s) return "int";
        if (s == 1) return "char";
        if (n == s - 1 && std::find(p, q, '.') != q) return "float";
        return "string";
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string str;
        std::cin >> str;
        std::cout << discern_type(str) << '\n';
    }
}
