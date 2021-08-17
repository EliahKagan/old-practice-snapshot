#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <set>

int main()
{
    std::set<int> s;

    auto q = 0;
    for (std::cin >> q; q > 0; --q) {
        auto y = 0, x = 0;
        std::cin >> y >> x;

        switch (y) {
        case 1:
            s.insert(x);
            break;

        case 2:
            s.erase(x);
            break;

        case 3:
            std::cout << (s.find(x) == s.end() ? "No" : "Yes") << '\n';
            break;

        default:
            assert(false);
        }
    }
}
