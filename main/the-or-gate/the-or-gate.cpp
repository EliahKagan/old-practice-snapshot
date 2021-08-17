#include <iostream>

namespace {
    bool read_disjunction()
    {
        auto n = 0, k = 0;
        std::cin >> n;

        while (n-- > 0) {
            std::cin >> k;

            if (k != 0) {
                while (n-- > 0) std::cin >> k;
                return true;
            }
        }

        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) std::cout << read_disjunction() << '\n';
}
