#include <iostream>
#include <set>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;

        std::multiset<int> s;
        for (auto i = n; i > 0; --i) {
            auto k = 0;
            std::cin >> k;
            s.insert(k);
        }

        auto sep = "";
        for (auto i = 1; i <= n; ++i) {
            std::cout << sep << s.count(i);
            sep = " ";
        }

        std::cout << '\n';
    }
}
