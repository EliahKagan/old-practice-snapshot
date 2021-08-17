class Solution {
public:
    static int minSubArrayLen(const int target, vector<int>& nums) noexcept;
};

int Solution::minSubArrayLen(const int target, vector<int>& nums) noexcept
{
    assert(target > 0);

    const auto last = cend(nums);
    auto first = cbegin(nums);
    partial_sum(first, last, begin(nums));

    const auto initial_mid = lower_bound(first, last, target);
    if (initial_mid == last) return 0; // whole array sums to less than target
    auto len = initial_mid + 1 - first;

    for (; first != last; ++first) {
        const auto mid = lower_bound(first, last, target + *first);
        if (mid != last) len = min(len, mid - first);
    }

    return static_cast<int>(len);
}
