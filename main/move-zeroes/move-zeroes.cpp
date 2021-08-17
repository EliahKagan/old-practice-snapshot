class Solution {
public:
    static void moveZeroes(vector<int>& nums) noexcept;
};

void Solution::moveZeroes(vector<int>& nums) noexcept
{
    stable_partition(begin(nums), end(nums),
                     [](const auto x) noexcept { return x != 0; });
}
