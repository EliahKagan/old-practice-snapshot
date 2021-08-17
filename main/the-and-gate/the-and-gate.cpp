#include <iostream>

namespace {
    bool read_conjunction()
    {
        auto n = 0, k = 0;
        std::cin >> n;

        while (n-- > 0) {
            std::cin >> k;

            if (k == 0) {
                while (n-- > 0) std::cin >> k;
                return false;
            }
        }

        return true;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) std::cout << read_conjunction() << '\n';
}
