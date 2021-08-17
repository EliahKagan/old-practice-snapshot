#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace {
    inline void toggle(std::unordered_set<int>& s, const int k)
    {
        const auto p = s.find(k);
        
        if (p == s.end()) s.insert(k);
        else s.erase(p);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::unordered_set<int> s;
        
        auto n = 0;
        std::cin >> n;
        
        for (n = (n + 1) * 2; n > 0; --n) {
            auto k = 0;
            std::cin >> k;
            
            toggle(s, k);
        }
        
        std::vector<int> v (s.cbegin(), s.cend());
        std::sort(v.begin(), v.end());
        std::cout << v.at(0) << ' ' << v.at(1) << '\n';
    }
}
