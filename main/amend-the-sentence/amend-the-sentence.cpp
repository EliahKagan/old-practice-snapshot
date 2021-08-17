#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

inline char low(const char c)
{
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

inline bool isup(const char c)
{
    return std::isupper(static_cast<unsigned char>(c));
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        
        auto p = s.cbegin();
        assert(p != s.cend());
        std::cout << low(*p);

        while (++p != s.cend()) {
            if (isup(*p))   std::cout << ' ' << low(*p);
            else            std::cout << *p;
        }

        std::cout << '\n';
    }
}
