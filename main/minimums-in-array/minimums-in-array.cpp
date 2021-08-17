#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iterator>
#include <limits>
#include <tuple>
#include <vector>

namespace {
    using Index = std::vector<int>::size_type;
    using Offset = std::vector<int>::difference_type;

    constexpr auto multiple_indices = std::numeric_limits<Index>::max();

    // Reads the specified number of integers into a vector from stdin.
    std::vector<int> read_record(const Index n)
    {
        std::vector<int> a (n);
        for (auto& x : a) (void)std::scanf("%d", &x);
        return a;
    }
    
    // Returns the minimum value and its index, if that value is unique.
    // Otherwise, returns the minimum value and multiple_indices as the index.
    std::tuple<int, Index> get_minval_and_index(const std::vector<int>& a)
    {
        const auto n = a.size();
        assert(0 < n && n < multiple_indices);

        auto val = a.front();
        Index idx {0u};

        for (Index j {1u}; j != n; ++j) {
            if (a[j] > val) continue;

            if (a[j] == val) idx = multiple_indices;
            else {
                val = a[j];
                idx = j;
            }
        }

        return std::make_tuple(val, idx);
    }

    // Returns the minimum value in a, but does not consider the value at
    // index i (which still must be a valid index). a must be nonempty.
    int minval_but_skip(const std::vector<int>& a, const Index i)
    {
        static constexpr auto max_safe_index =
                static_cast<Index>(std::numeric_limits<Offset>::max());

        const auto n = a.size();
        assert(i < n && n <= max_safe_index);

        if (i == 0)
            return *std::min_element(std::next(a.cbegin()), a.cend());

        if (i + 1u == n)
           return *std::min_element(a.cbegin(), std::prev(a.cend()));

        const auto p = a.cbegin(), q = p + static_cast<Offset>(i);

        return std::min(*std::min_element(p, q),
                        *std::min_element(std::next(q), a.cend()));
    }

    // Assumes the task is possible.
    int get_min_sum_from_different_indices(const std::vector<int>& a,
                                           const std::vector<int>& b)
    {
        int a_min {}, b_min {};
        Index a_ind {}, b_ind {};
        std::tie(a_min, a_ind) = get_minval_and_index(a);
        std::tie(b_min, b_ind) = get_minval_and_index(b);

        if (a_ind != b_ind || a_ind == multiple_indices
                           || b_ind == multiple_indices)
            return a_min + b_min; // best-case scenario, we can use both minima

        return std::min(a_min + minval_but_skip(b, b_ind),  // uses min from a
                        b_min + minval_but_skip(a, a_ind)); // uses min from b
    }

    // Returns the answer or, if the task is impossible, returns fallback.
    int get_min_sum_from_different_indices(const std::vector<int>& a,
                                           const std::vector<int>& b,
                                           const int fallback)
    {
        const auto n = a.size();
        assert(n != 0u && b.size() == n);

        return n == 1u ? fallback : get_min_sum_from_different_indices(a, b);
    }
}

int main()
{
    constexpr auto impossible = -1;

    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        std::size_t n {};
        (void)std::scanf("%zu", &n);

        const auto a = read_record(n), b = read_record(n);
        const auto ans = get_min_sum_from_different_indices(a, b, impossible);

        std::printf("%d\n", ans);
    }
}
