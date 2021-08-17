#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>

namespace {
    using Index = std::vector<int>::size_type;
    
    std::vector<int> get_min_op_counts(const Index nmax)
    {
        std::vector<int> tab (nmax + 1u);
        std::queue<Index> q;
        q.push(1u);
        
        for (auto op_count = 1; !q.empty(); ++op_count) {
            for (auto len = q.size(); len != 0u; --len) {
                const auto n = q.front();
                q.pop();
                
                if (n <= nmax && tab[n] == 0) {
                    tab[n] = op_count;
                    q.push(n * 2u);
                    q.push(n + 1u);
                }
            }
        }
        
        return tab;
    }
}

int main()
{
    static constexpr Index nmax {10000u};
    const auto tab = get_min_op_counts(nmax);
    
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Index n {};
        std::cin >> n;
        std::cout << tab.at(n) << '\n';
    }
}
