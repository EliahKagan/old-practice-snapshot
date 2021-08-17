#include <bitset>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace {
    std::vector<int> read_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }
    
    bool has_equal_disjoint_pair_sums(const std::vector<int>& values)
    {
        static constexpr std::size_t index_range {101};
        using Indices = std::bitset<index_range>;
        
        const auto size = values.size();
        if (size < 4u) return false;
        if (size >= index_range) throw std::length_error{"too many elements"};
        
        std::unordered_map<int, std::bitset<index_range>> sum_indices;
        
        const auto last = size - 1u;
        for (std::size_t i {0u}; i != last; ++i) {
            for (auto j = i + 1u; j != size; ++j) {
                const auto sum = values[i] + values[j];
                const auto p = sum_indices.find(sum);
                
                if (p == sum_indices.end()) {
                    auto& indices = sum_indices[sum];
                    indices.set(i);
                    indices.set(j);
                } else {
                    auto& indices = p->second;
                    if (!(indices[i] || indices[j])) return true;
                    indices.set(i);
                    indices.set(j);
                }
            }
        }
        
        return false;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t)
        std::cout << has_equal_disjoint_pair_sums(read_record()) << '\n';
}
