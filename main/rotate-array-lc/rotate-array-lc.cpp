class Solution {
public:
    static void rotate(vector<int>& nums, ptrdiff_t k) noexcept;
};

void Solution::rotate(vector<int>& nums, const ptrdiff_t k) noexcept
{
    if (nums.empty()) return;

    const auto left = begin(nums);
    const auto right = end(nums);
    const auto mid =  left + k % (right - left);

    reverse(left, right);
    reverse(left, mid);
    reverse(mid, right);
}
