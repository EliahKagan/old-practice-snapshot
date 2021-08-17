class Solution {
public:
    static int minSubArrayLen(int target,
                              const vector<int>& nums) noexcept;
};

int Solution::minSubArrayLen(const int target,
                             const vector<int>& nums) noexcept
{
    assert(target > 0);
    static constexpr auto inf = numeric_limits<ptrdiff_t>::max();

    auto len = inf;
    auto sum = 0;

    const auto last = cend(nums);

    for (auto left = cbegin(nums), right = left; right != last; ++right) {
        if ((sum += *right) < target) continue;

        for (; *left <= sum - target; ++left) sum -= *left;
        len = min(len, right + 1 - left);
    }

    return len == inf ? 0 : static_cast<int>(len);
}
