class Solution {
public:
    static int maxSubArray(const vector<int>& nums) noexcept;
};

namespace {
    template<typename It>
    using Value = typename iterator_traits<It>::value_type;

    template<typename It>
    constexpr Value<It> max_partial_sum(const It first, const It last) noexcept
    {
        Value<It> best {}, cur {};

        for_each(first, last, [&](const Value<It> elem) noexcept {
            best = max(best, cur += elem);
        });

        return best;
    }

    template<typename It>
    constexpr int contiguous_max_crossing(const It first, const It mid,
                                          const It last) noexcept
    {
        const auto left_sum = max_partial_sum(make_reverse_iterator(mid),
                                              make_reverse_iterator(first));

        const auto right_sum = max_partial_sum(next(mid), last);

        return left_sum + *mid + right_sum;
    }

    template<typename It>
    constexpr int contiguous_max(const It first, const It last) noexcept
    {
        if (last - first < 2)
            return last == first ? numeric_limits<Value<It>>::min() : *first;

        const auto mid = first + (last - first) / 2;

        return max(max(contiguous_max(first, mid), contiguous_max(mid, last)),
                   contiguous_max_crossing(first, mid, last));
    }
}

int Solution::maxSubArray(const vector<int>& nums) noexcept
{
    return contiguous_max(cbegin(nums), cend(nums));
}
