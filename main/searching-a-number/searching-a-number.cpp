#include <iostream>

namespace {
    inline void consume_input(int count)
    {
        for (int x; count > 0; --count) std::cin >> x;
    }

    int find_in_input(const int n, const int k)
    {
        for (auto i = 1; i <= n; ++i) {
            auto x = 0;
            std::cin >> x;

            if (x == k) {
                consume_input(n - i);
                return i;
            }
        }

        return -1;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, k = 0;
        std::cin >> n >> k;
        std::cout << find_in_input(n, k) << '\n';
    }
}
