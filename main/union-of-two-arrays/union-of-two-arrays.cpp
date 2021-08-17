#include <iostream>
#include <set>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, m = 0;
        std::cin >> n >> m;

        std::set<int> s;
        for (auto i = n + m; i > 0; --i) {
            auto k = 0;
            std::cin >> k;
            s.insert(k);
        }

        auto sep = "";
        for (const auto k : s) {
            std::cout << sep << k;
            sep = " ";
        }

        std::cout << '\n';
    }
}
