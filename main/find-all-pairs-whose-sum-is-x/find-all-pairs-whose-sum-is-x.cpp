#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, m = 0, x = 0;
        std::cin >> n >> m >> x;
        std::unordered_set<int> s;
        
        for (auto e = 0; n > 0; --n) {
            std::cin >> e;
            s.insert(e);
        }
        
        std::vector<std::pair<int, int>> a;
        
        for (auto e = 0; m > 0; --m) {
            std::cin >> e;
            if (s.find(x - e) != s.cend()) a.emplace_back(x - e, e);
        }
        
        if (a.empty()) {
            std::cout << "-1\n";
            continue;
        }
        
        std::sort(a.begin(), a.end());
        
        std::cout << a.front().first << ' ' << a.front().second;
        for (auto p = a.cbegin(); ++p != a.cend(); )
            std::cout << ", " << p->first << ' ' << p->second;
        
        std::cout << '\n';
    }
}
