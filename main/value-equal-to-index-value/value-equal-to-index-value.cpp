#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto got_match = false;
        auto n = 0;
        std::cin >> n;
        
        for (auto i = 1; i <= n; ++i) {
            auto k = 0;
            std::cin >> k;
            if (i == k) {
                if (got_match) std::cout << ' ';
                std::cout << i;
                got_match = true;
            }
        }

        if (!got_match) std::cout << "Not Found";
        std::cout << '\n';
    }
}
