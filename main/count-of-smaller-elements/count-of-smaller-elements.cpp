#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> read_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a (n);
        for (auto& e : a) std::cin >> e;
        return a;
    }
    
    std::vector<int>::difference_type
    count_less_or_equal(const std::vector<int>& a, const int x)
    {
        return std::upper_bound(a.cbegin(), a.cend(), x) - a.cbegin();
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto a = read_record();
        
        auto x = 0;
        std::cin >> x;
        
        std::cout << count_less_or_equal(a, x) << '\n';
    }
}
