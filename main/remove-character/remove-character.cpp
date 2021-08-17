#include <iostream>
#include <set>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s, r;
        std::cin >> s >> r;
        const std::set<char> removals (r.cbegin(), r.cend());
        const auto not_found = removals.cend();
        
        for (const auto c : s)
            if (removals.find(c) == not_found) std::cout << c;

        std::cout << '\n';
    }
}
