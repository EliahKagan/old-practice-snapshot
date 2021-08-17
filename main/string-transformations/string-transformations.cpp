#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::string s;
    std::getline(std::cin, s);

    auto q = 0;
    for (std::cin >> q; q > 0; --q) {
        std::string::difference_type a {-1}, b {-1};
        std::cin >> a >> b;
        assert(0 <= a && a <= b && b < static_cast<decltype(b)>(s.size()));

        const auto p = s.begin();
        std::reverse(p + a, p + b + 1);
        std::cout << s << '\n';
    }
}
