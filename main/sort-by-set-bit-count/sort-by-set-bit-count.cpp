#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> get(std::vector<int>::size_type n)
    {
        std::vector<int> a;
        for (a.reserve(n); n != 0u; --n) {
            auto x = 0;
            std::cin >> x;
            a.push_back(x);
        }
        
        return a;
    }
    
    std::vector<int> put(const std::vector<int>& a)
    {
        const auto q = a.cend();
        auto p = a.cbegin();
        
        if (p != q)
            for (std::cout << *p; ++p != q; ) std::cout << ' ' << *p;
        
        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        std::cin >> n;
        auto a = get(n);
        
        std::stable_sort(a.begin(), a.end(), [](const int x, const int y) {
            return __builtin_popcount(x) > __builtin_popcount(y);
        });
        
        put(a);
    }
}
