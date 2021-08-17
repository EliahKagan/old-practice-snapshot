class Solution {
public:
    static int minSubArrayLen(int target,
                              const vector<int>& nums) noexcept;
};

int Solution::minSubArrayLen(int target,
                             const vector<int>& nums) noexcept
{
    assert(target > 0);
    static constexpr auto inf = numeric_limits<ptrdiff_t>::max();

    auto len = inf;

    const auto last = cend(nums);

    for (auto left = cbegin(nums), right = left; right != last; ++right) {
        if ((target -= *right) > 0) continue;

        for (; target + *left <= 0; ++left) target += *left;
        len = min(len, right + 1 - left);
    }

    return len == inf ? 0 : static_cast<int>(len);
}
