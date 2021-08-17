#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    std::vector<int> get_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a (n);
        for (auto& e : a) std::cin >> e;
        
        return a;
    }
    
    void put_record(const std::vector<int>& a)
    {
        auto sep = "";
        for (const auto e : a) {
            std::cout << sep << e;
            sep = " ";
        }
        
        std::cout << '\n';
    }
    
    void special_sort(std::vector<int>& a)
    {
        std::sort(std::begin(a), std::end(a), [](const int x, const int y) {
            if (x % 2 != y % 2) return x % 2 > y % 2; // odd before even
            if (x % 2 != 0) return x > y; // odd descending
            return x < y; // even ascending
        });
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = get_record();
        special_sort(a);
        put_record(a);
    }
}
