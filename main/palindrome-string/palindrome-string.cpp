#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <string>

namespace {
    void rtrim(std::string& s)
    {
        // See https://stackoverflow.com/q/216823 by Milan Babuškov.
        s.erase(s.find_last_not_of(" \t\r\n") + 1u);
    }

    bool is_palindrome(const std::string& s)
    {
        auto p = s.cbegin();
        auto q = s.crbegin();
        for (auto m = s.size() / 2u; m != 0u; --m, ++p, ++q)
            if (*p != *q) return false;

        return true;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string::size_type n;
        std::cin >> n >> std::ws;
        
        std::string s;
        std::getline(std::cin, s);
        rtrim(s);
        assert(n != 0u && s.size() == n);

        std::cout << (is_palindrome(s) ? "Yes" : "No") << '\n';
    }
}
