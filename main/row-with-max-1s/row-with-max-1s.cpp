#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        auto m = 0;
        std::cin >> n >> m;

        std::vector<int> sums (n);
        for (auto& sum : sums) {
            for (auto i = m; i > 0; --i) {
                auto b = false;
                std::cin >> b;
                if (b) ++sum;
            }
        }

        const auto p = std::max_element(sums.cbegin(), sums.cend());
        std::cout << p - sums.cbegin() << '\n';
    }
}
