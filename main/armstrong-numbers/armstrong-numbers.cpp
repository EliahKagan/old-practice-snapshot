#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    inline int cube(const int k)
    {
        return k * k * k;
    }

    bool is_armstrong(const int n)
    {
        assert(100 <= n && n < 1000);

        std::ostringstream ss;
        ss << n;
        const auto s = ss.str();

        return cube(s[0] - '0') + cube(s[1] - '0') + cube(s[2] - '0') == n;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;
        std::cout << (is_armstrong(n) ? "Yes" : "No") << '\n';
    }
}
