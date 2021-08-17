#include <iostream>
#include <limits>
#include <vector>

namespace {
    using Index = std::vector<int>::size_type;

    // Finds the maximum distance between elements where the left element is
    // not greater than the right element.
    Index compute_best_distance(std::vector<int> a)
    {
        Index best_distance {0u};
        auto prev_right_index = a.size();
        auto best_right_index = prev_right_index - 1u;

        auto prev_left_elem = std::numeric_limits<int>::max();
        auto prev_right_index = a.size();


        for (Index i {0u}; i < a.size() - best_distance; ++i) {
            if (a[i] >= prev_left_elem) continue;

        }
    }
}

