#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

namespace {
    class DisjointSets {
    public:
        explicit DisjointSets(int count);

        void unite(int i, int j) noexcept;

        std::pair<int, int> minmax_nontrivial_component_sizes() const noexcept;

    private:
        int count() const noexcept;

        int find_set(int i) noexcept;

        void join(int parent, int child) noexcept;

        std::vector<int> parents_;
        std::vector<int> sizes_;
    };

    DisjointSets::DisjointSets(const int count)
        : parents_(count), sizes_(count, 1)
    {
        std::iota(begin(parents_), end(parents_), 0);
    }

    void DisjointSets::unite(int i, int j) noexcept
    {
        // Find the ancestors and stop if they are the same.
        i = find_set(i);
        j = find_set(j);
        if (i == j) return;

        // Union by size.
        if (sizes_[i] < sizes_[j])
            join(j, i);
        else
            join(i, j);
    }

    std::pair<int, int>
    DisjointSets::minmax_nontrivial_component_sizes() const noexcept
    {
        auto min = std::numeric_limits<int>::max();
        auto max = std::numeric_limits<int>::min();

        for (auto i = 0; i < count(); ++i) {
            if (i == parents_[i] && sizes_[i] > 1) {
                min = std::min(min, sizes_[i]);
                max = std::max(max, sizes_[i]);
            }
        }

        return std::make_pair(min, max);
    }

    inline int DisjointSets::count() const noexcept
    {
        return static_cast<int>(parents_.size());
    }

    int DisjointSets::find_set(int i) noexcept
    {
        assert(0 <= i && i < count());

        // Find the ancestor.
        auto j = i;
        while (j != parents_[j]) j = parents_[j];

        // Compress the path.
        while (i != j) {
            const auto parent = parents_[i];
            parents_[i] = j;
            i = parent;
        }

        return j;
    }

    inline void DisjointSets::join(const int parent, const int child) noexcept
    {
        sizes_[parent] += sizes_[child];
        parents_[child] = parent;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int n {};
    std::cin >> n;
    DisjointSets sets {n * 2 + 1};

    while (n-- > 0) {
        int i {}, j {};
        std::cin >> i >> j;
        sets.unite(i, j);
    }

    int min {}, max {};
    std::tie(min, max) = sets.minmax_nontrivial_component_sizes();
    std::cout << min << ' ' << max << '\n';
}
