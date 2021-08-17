#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

namespace {
    constexpr auto visited = std::numeric_limits<std::size_t>::max();
    
    std::vector<std::size_t>
    normalize_to_permutation(const std::vector<int>& values)
    {
        std::vector<std::size_t> permutation (values.size());
        const auto p = std::begin(permutation), q = std::end(permutation);

        std::iota(p, q, static_cast<std::size_t>(0u));

        std::sort(p, q, [&values](const std::size_t i, const std::size_t j) {
            return values[i] < values[j];
        });

        return permutation;
    }
    
    // Traverses the cycle of the permutation that begins at the index start,
    // marking each element visited and returning the number of positions
    // traversed (always at least 1).
    int traverse_and_mark_cycle(std::vector<std::size_t>& permutation,
                                const std::size_t start)
    { 
        auto cycle_length = 0;
        
        auto cur = start;
        do {
            ++cycle_length;
            const auto next = permutation[cur];
            permutation[cur] = visited;
            cur = next;
        }
        while (cur != start);
        
        return cycle_length;
    }

    int compute_min_swaps(const std::vector<int>& values)
    {
        auto permutation = normalize_to_permutation(values);
        const auto length = permutation.size();

        auto swaps = 0;
        for (std::size_t i {0u}; i != length; ++i) {
            if (permutation[i] != visited)
                swaps += traverse_and_mark_cycle(permutation, i) - 1;
        }

        return swaps;
    }

    std::vector<int> read_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> values (n);
        for (auto& elem : values) std::cin >> elem;
        return values;
    }

    void negate(std::vector<int>& values)
    {
        for (auto& elem : values) elem = -elem;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto values = read_record();
    const auto forward_solution = compute_min_swaps(values);

    negate(values);
    const auto backward_solution = compute_min_swaps(values);

    std::cout << std::min(forward_solution, backward_solution) << '\n';
}
