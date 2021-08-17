#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>
#include <cstdio>
#include <unordered_map>

namespace {
    // Reads and maintains a running sum of numbers, storing how often each
    // partial sum occurs in counts, which maps sums to their frequencies.
    inline void read_partial_sums(std::unordered_map<int, int>& counts)
    {
        counts.clear();
        counts.emplace(0, 1);

        auto n = 0;
        (void)std::scanf("%d", &n);
        assert(n >= 0);

        for (auto sum = 0, elem = 0; n-- != 0; ) {
            (void)std::scanf("%d", &elem);
            sum += elem;
            ++counts[sum]; // increment or insert a 1
        }
    }

    // Given the frequencies of all partial sums from the leftmost element,
    // efficiently computes the number of partial sums starting or ending at
    // any element that are zero.
    inline int count_zero_deltas(const std::unordered_map<int, int>& counts)
    {
        auto acc = 0;
        for (const auto& kv : counts) acc += kv.second * (kv.second - 1) / 2;
        return acc;
    }
}

int main()
{
    std::unordered_map<int, int> counts;
    
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        read_partial_sums(counts);
        std::printf("%d\n", count_zero_deltas(counts));
    }
}
