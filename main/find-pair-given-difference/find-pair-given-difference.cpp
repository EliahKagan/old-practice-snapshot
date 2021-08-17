#include <iostream>
#include <unordered_set>
#include <vector>

namespace {
    std::vector<int> read_record(const std::vector<int>::size_type len)
    {
        std::vector<int> a (len);
        for (auto& x : a) std::cin >> x;
        return a;
    }
    
    bool has_pair_difference(const std::vector<int>& a, const int difference)
    {
        std::unordered_set<int> s; // stores upper and lower complements
        
        for (const auto x : a) {
            if (s.find(x) != s.end()) return true;
            
            s.insert(x + difference);
            s.insert(x - difference);
        }
        
        return false;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type len {};
        auto difference = 0;
        
        std::cin >> len >> difference;
        const auto a = read_record(len);
        
        std::cout << (has_pair_difference(a, difference) ? "1\n" : "-1\n");
    }
}
