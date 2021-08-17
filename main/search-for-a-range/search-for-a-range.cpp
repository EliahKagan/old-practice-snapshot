class Solution {
public:
    static vector<int> searchRange(const vector<int>& nums, int target);
};

vector<int> Solution::searchRange(const vector<int>& nums, const int target)
{
    const auto beg = cbegin(nums);

    vector<int>::const_iterator left, right;
    tie(left, right) = equal_range(beg, cend(nums), target);

    if (left == right) return {-1, -1};
    return {left - beg, right - 1 - beg};
}
