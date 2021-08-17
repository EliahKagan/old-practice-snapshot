class Solution {
public:
    static int maxSubArray(const vector<int>& nums) noexcept;
};

int Solution::maxSubArray(const vector<int>& nums) noexcept
{
    auto acc = numeric_limits<int>::min();
    auto cur = 0;

    for (const auto elem : nums) {
        cur = max(cur, 0) + elem;
        acc = max(acc, cur);
    }

    return acc;
}
