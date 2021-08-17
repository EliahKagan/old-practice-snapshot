#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

namespace {
    int sum_digits(const std::string& n)
    {
        return std::accumulate(n.cbegin(), n.cend(), 0,
                [](const int acc, const char d) { return acc + (d - '0'); });
    }

    bool is_palindrome(const std::string& s)
    {
        assert(!s.empty());

        for (auto p = s.cbegin(), q = s.cend() - 1; p < q; ++p, --q)
            if (*p != *q) return false;

        return true;
    }

    template<typename T>
    bool repr_is_palindrome(const T n)
    {
        std::ostringstream ss;
        ss << n;
        return is_palindrome(ss.str());
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string n;
        std::cin >> n;

        std::cout << (repr_is_palindrome(sum_digits(n)) ? "YES" : "NO")
                  << '\n';
    }
}
