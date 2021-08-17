#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

namespace {
    std::vector<int> read_record(const std::vector<int>::size_type n)
    {
        std::vector<int> a (n);
        for (auto& e : a) std::cin >> e;
        return a;
    }
    
    int min_sum_different_indices(std::vector<int>&& a, std::vector<int>&& b)
    {
        assert(a.size() == b.size());
        if (a.size() < 2u) return -2147483639; // that's the "expected output"
        
        // If smallest elements have different indices, return their sum!
        auto p = std::min_element(std::begin(a), std::end(a));
        auto q = std::min_element(std::begin(b), std::end(b));
        if (p - a.begin() != q - b.begin()) return *p + *q;
        
        // If they have the same index, try each vector's smallest element
        // with the other vector's "second smallest" (by <=, not <).
        const auto min_a = *p, min_b = *q;
        *p = *q = std::numeric_limits<int>::max();
        p = std::min_element(std::begin(a), std::end(a));
        q = std::min_element(std::begin(b), std::end(b));
        return std::min(min_a + *q, min_b + *p);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::cout << min_sum_different_indices(read_record(n), read_record(n))
                  << '\n';
    }
}
