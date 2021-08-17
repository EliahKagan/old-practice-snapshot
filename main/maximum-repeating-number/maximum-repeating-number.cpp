#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::vector<int>::size_type k {};
        std::cin >> n >> k;
        
        std::vector<int> freqs (k);
        while (n-- > 0) {
            std::vector<int>::size_type i {};
            std::cin >> i;
            ++freqs.at(i);
        }

        const auto p = std::max_element(freqs.cbegin(), freqs.cend());
        std::cout << p - freqs.cbegin() << '\n';
    }
}
