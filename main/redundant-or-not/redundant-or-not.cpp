#include <iostream>
#include <set>

int main()
{
    std::set<int> s;

    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        auto k = 0;
        std::cin >> k;

        if (s.find(k) == s.end()) {
            s.insert(k);
            std::cout << "ADDED\n";
        }
        else std::cout << "REDUNDANT\n";
    }
}
