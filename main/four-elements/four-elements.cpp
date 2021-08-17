#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
    using Index = std::vector<int>::size_type;
    
    using IndexPair = std::pair<Index, Index>;
    
    template<typename T>
    using IndexPairMap = std::unordered_map<T, std::vector<IndexPair>>;
    
    std::vector<int> read_record()
    {
        Index n {};
        std::cin >> n;
        
        std::vector<int> a (n);
        for (auto& e : a) std::cin >> e;
        return a;
    }
    
    IndexPairMap<int> get_two_element_sums(const std::vector<int>& a)
    {
        IndexPairMap<int> two_sums;
        
        const auto jstop = a.size(), istop = jstop - 1u;
        for (Index i {0u}; i != istop; ++i) {
            for (auto j = i + 1u; j != jstop; ++j)
                two_sums[a[i] + a[j]].emplace_back(i, j);
        }
        
        return two_sums;
    }
    
    bool have_disjoint_pairs(const std::vector<IndexPair>& lhs,
                             const std::vector<IndexPair>& rhs)
    {
        for (const auto& u : lhs) {
            for (const auto& v : rhs) {
                if (u.first != v.first && u.first != v.second
                        && u.second != v.first && u.second != v.second)
                    return true;
            }
        }
        
        return false;
    }
    
    bool has_four_element_sum(const std::vector<int>& a, const int x)
    {
        if (a.size() < 4u) return false;
        
        const auto two_sums = get_two_element_sums(a);
        const auto stop = two_sums.cend();
        
        for (auto p = two_sums.cbegin(); p != stop; ++p) {
            const auto q = two_sums.find(x - p->first); // find complement
            if (q != stop && have_disjoint_pairs(p->second, q->second))
                return true;
        }
        
        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto a = read_record();
        
        auto x = 0;
        std::cin >> x;
        
        std::cout << has_four_element_sum(a, x) << '\n';
    }
}
