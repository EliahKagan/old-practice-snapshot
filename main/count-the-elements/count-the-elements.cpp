#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> read_record(const std::vector<int>::size_type n)
    {
        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }
    
    std::vector<int> read_record_as_sorted(const std::vector<int>::size_type n)
    {
        auto a = read_record(n);
        std::sort(a.begin(), a.end());
        return a;
    }
    
    inline std::vector<int>::difference_type
    count_less_or_equal(const std::vector<int>& b, const int x)
    {
        return std::upper_bound(b.cbegin(), b.cend(), x) - b.cbegin();
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        std::cin >> n;
        const auto a = read_record(n), b = read_record_as_sorted(n);
        
        auto sep = "";
        for (const auto x : a) {
            std::cout << sep << count_less_or_equal(b, x);
            sep = ",";
        }
        
        std::cout << '\n';
    }
}
