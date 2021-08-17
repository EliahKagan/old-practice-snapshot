class Solution {
public:
    static bool containsDuplicate(const vector<int>& nums);
};

bool Solution::containsDuplicate(const vector<int>& nums)
{
    unordered_set<int> seen;
    for (const auto& val : nums) {
        if (seen.find(val) != seen.end()) return true;
        seen.insert(val);
    }

    return false;
}
