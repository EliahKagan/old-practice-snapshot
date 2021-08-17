#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, int> m;

    auto q = 0;
    for (std::cin >> q; q > 0; --q) {
        auto t = 0;
        std::string x;
        std::cin >> t >> x;

        switch (t) {
        case 1:
            {
                auto y = 0;
                std::cin >> y;
                m[x] += y;
            }

            break;

        case 2:
            m.erase(x);
            break;

        case 3:
            std::cout << m[x] << '\n';
            break;

        default:
            assert(false);
        }
    }
}
